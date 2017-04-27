<?php
class NBNClient
{
    private $token;
 
    function Login($username, $password)
    {
        $url = "https://data.nbn.org.uk/api/user/login?username=" . $username. 
                "&password=" . $password . "&remember=true";
 
        $ch = curl_init();
 
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
 
        $json = curl_exec($ch);
        $response = $this->CurlDecodeResponse($json, $ch);
        curl_close($ch);
 
        if (property_exists($repsonse, 'token')) {
          $this->token = rtrim($response->token, "=");
        }
    }
 
    function CurlGetString($url)
    {
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
 
        $json = curl_exec($ch);
        $response = $this->CurlDecodeResponse($json, $ch);
        curl_close($ch);
        return $response;
    }
 
    function CurlPostData($url, $postData)
    {
        $fields_string = "";
        foreach($postData as $key=>$value)
        {
            $fields_string .= $key . "=" . $value . "&";
        }
        $fields_string = rtrim($fields_string, "&");
 
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
 
        curl_setopt($ch, CURLOPT_COOKIE, "nbn.token_key=".$this->token);
 
        curl_setopt($ch, CURLOPT_POST, count($postData));
        curl_setopt($ch, CURLOPT_POSTFIELDS, $fields_string);
 
        curl_setopt($ch, CURLOPT_TIMEOUT, 120);
        $json = curl_exec($ch);
        $response = $this->CurlDecodeResponse($json, $ch);
        curl_close($ch); 
        return $response;
    }
    
    function CurlDecodeResponse($json, $ch) 
    {
      if ($json === FALSE) {
        // Check for error in response from curl_exec.
        $response = array();
        $response['error'] = curl_error($ch);
        $response['error'] = str_replace(array("\r\n", "\n", "\r"), '<br />', $response['error']);
      }
      elseif ($json === '') {
        // Check for no results returned.
        $response = array();
        $response['error'] = 'The NBN Gateway responded with no data. Ensure the settings are correct.';
      }
      else {
        // Decode response.
        $response = json_decode($json, TRUE);

        // Check for error during decoding.
        if (!isset($response)) {
          $response = array();
          switch (json_last_error()) {
            case JSON_ERROR_DEPTH:
              $response['error'] = 'Maximum stack depth exceeded';
              break;
            case JSON_ERROR_STATE_MISMATCH:
              $response['error'] = 'Underflow or the modes mismatch';
              break;
            case JSON_ERROR_CTRL_CHAR:
              $response['error'] = 'Unexpected control character found';
              break;
            case JSON_ERROR_SYNTAX:
              /* If the NBN Gateway is down it may redirect to a status page.
               * The response looks like
               * <html><head>
               * <title>302 Found</title>
               * </head><body>
               * <h1>Found</h1>
               * <p>The document has moved <a href="http://status.nbn.org.uk/">here</a>.</p>
               * </body></html>
               * 
               * This results in a malformed JSON error.
               */
              $response['error'] = 'Syntax error, malformed JSON';
              break;
            case JSON_ERROR_UTF8:
              $response['error'] = 'Malformed UTF-8 characters, possibly incorrectly encoded';
              break;
            default:
              $response['error'] = 'Unknown error';
              break;
          }
          $response['error'] = 'Error while decoding JSON. ' . $response['error'];
        }
      }
      
      // Return decoded response object or error array.
      return $response;
    }

    function GetViceCounties()
    {
        $url = "https://data.nbn.org.uk/api/siteBoundaryDatasets/GA000344/siteBoundaries";
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function GetTaxonOutputGroups()
    {
        $url = "https://data.nbn.org.uk/api/taxonOutputGroups";
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function GetDesignations()
    {
        $url = "https://data.nbn.org.uk/api/designations";
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function GetSiteSpecies($viceCounty, $taxonOutputGroup, $designation)
    {
        $url = "https://data.nbn.org.uk/api/taxonObservations/species?featureID=" . 
                $viceCounty . "&taxonOutputGroup=" . $taxonOutputGroup;
        if(!(strlen($designation) == 0))
        {
            $url = $url . "&designation=" . $designation;
        }
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function GetSiteDatasets($viceCounty, $taxonOutputGroup, $designation)
    {
        $url = "https://data.nbn.org.uk/api/taxonObservations/datasets?featureID=" .
                $viceCounty . "&taxonOutputGroup=" . $taxonOutputGroup;
        if(!(strlen($designation) == 0))
        {
            $url = $url . "&designation=" . $designation;
        }
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function GetTenKmSpecies($gridReference)
    {
        $url = "https://data.nbn.org.uk/api/taxonObservations/species?gridRef=" .
                $gridReference;
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function GetTenKmDatasets($gridReference)
    {
        $url = "https://data.nbn.org.uk/api/taxonObservations/datasets?gridRef=" .
                $gridReference;
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function GetTaxonSearchResult($query)
    {
        $url = "https://data.nbn.org.uk/api/taxa?q=" . $query;
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function GetTaxonomy($taxonVersionKey)
    {
        $url = "https://data.nbn.org.uk/api/taxa/" . $taxonVersionKey;
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function GetTaxonParent($taxonVersionKey)
    {
        $url = "https://data.nbn.org.uk/api/taxa/" . $taxonVersionKey . "/parent";
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function GetTaxonParents($taxonVersionKey)
    {
        $parents = array();
        do
        {
            $parent = $this->GetTaxonParent($taxonVersionKey);
            if($parent != NULL)
            {
                $taxonVersionKey = $parent->taxonVersionKey;
                $parents[] = $parent;
            }
        }
        while($parent != NULL);
        $parents = array_reverse($parents);
        return $parents;
    }
 
    function GetTaxonChildren($taxonVersionKey)
    {
        $url = "https://data.nbn.org.uk/api/taxa/" . $taxonVersionKey . "/children";
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function PostRecordsForDatasetAndGridRef($datasetKey, $gridReference)
    {
        $url = "https://data.nbn.org.uk/api/taxonObservations";
        $postData = array();
        $postData["datasetKey"] = $datasetKey;
        $postData["gridRef"] = $gridReference;
        $response = $this->CurlPostString($url, $postData);
        return $response;
    }
 
    function GetRecordsForWKTDesignationDates($wkt, $designation, $startYear, $endYear)
    {
        $url = "https://data.nbn.org.uk/api/taxonObservations?polygon=" . $wkt .
                "&designation=" . $designation . "&startYear=" . $startYear . 
                "&endYear=" . $endYear;
        $response = $this->CurlGetString($url);
        return $response;
    }
 
    function PostRecordsForWKTDesignationDates($wkt, $designation, $startyear, $endyear)
    {
        $url = "https://data.nbn.org.uk/api/taxonObservations";
        $postData = array();
        $postData["polygon"] = $wkt;
        $postData["designation"] = $designation;
        $postData["startYear"] = $startyear;
        $postData["endYear"] = $endyear;
        $response = $this->CurlPostData($url, $postData);
        return $response;
    }
 
    function PostRecordsForWKTDesignationDatasetDates($wkt, $designation, 
            $datasetkey, $startyear, $endyear)
    {
        $url = "https://data.nbn.org.uk/api/taxonObservations";
        $postData = array();
        $postData["polygon"] = $wkt;
        $postData["designation"] = $designation;
        $postData["datasetKey"] = $datasetkey;
        $postData["startYear"] = $startyear;
        $postData["endYear"] = $endyear;
        $response = $this->CurlPostData($url, $postData);
        return $response;
    }
    
    function GetOrganisationDatasets($organisation)
    {
        $url = "https://data.nbn.org.uk/api/organisations/" . $organisation . 
                "/datasets";
        $response = $this->CurlGetString($url);
        return $response;
    }
    
    function GetOrganisationContributedDatasets($organisation)
    {
        $url = "https://data.nbn.org.uk/api/organisations/" . $organisation . 
                "/contributedDatasets";
        $response = $this->CurlGetString($url);
        return $response;
    }
    
}
