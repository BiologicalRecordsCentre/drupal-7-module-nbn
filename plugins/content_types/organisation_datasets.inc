<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Organisation datasets'),
  'description' => t('Given an organisation id, returns datasets'),
  'category' => t('NBN'),
  'edit form' => 'nbn_organisation_datasets_edit_form', // returns settings form for pane.
  'render callback' => 'nbn_organisation_datasets_render', // returns renderable content.
  'admin info' => 'nbn_organisation_datasets_admin_info', // returns information displayed on admin screen.
  'all contexts' => TRUE,
);

/**
* 'Edit form' callback for the content type.
*/
function nbn_organisation_datasets_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $field_conf = $form_state['conf']['fields'];
  $option_conf = $form_state['conf']['options'];
  $form['organisation'] = array(
    '#type' => 'textfield',
    '#title' => t('NBN organisation id'),
    '#description' => t('You can determine the id of an organisation from its '
            . 'url at https://data.nbn.org.uk/Organisations. Either insert an'
            . 'integer or a %substitution token for a field.'),
    '#default_value' => isset($conf['organisation']) ? $conf['organisation'] : '4',
  );
  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('Dataset type'),  
    '#default_value' => isset($conf['type']) ? $conf['type'] : 'provided',
    '#options' => array(
        'provided' => t('Provided by organisation'),
        'contributed' => t('Contributed to by organisation'),
    ),
  );
  $form['fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fields to display')  
  );
  $form['fields']['href'] = array(
    '#type' => 'checkbox',
    '#title' => t('Dataset record web page url'),  
    '#default_value' => isset($field_conf['href']) ? $field_conf['href'] : 0,
  );
  // Field names match those in the NBN response
  $form['fields']['organisationHref'] = array(
    '#type' => 'checkbox',
    '#title' => t('Organisation record web service url'),  
    '#default_value' => isset($field_conf['organisation_href']) ? $field_conf['organisation_href'] : 0,
  );
  $form['fields']['key'] = array(
    '#type' => 'checkbox',
    '#title' => t('Dataset key'),  
    '#default_value' => isset($field_conf['key']) ? $field_conf['key'] : 0,
  );
  $form['fields']['title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Dataset title'),  
    '#default_value' => isset($field_conf['title']) ? $field_conf['title'] : 1,
  );
  $form['fields']['description'] = array(
    '#type' => 'checkbox',
    '#title' => t('Dataset description'),  
    '#default_value' => isset($field_conf['description']) ? $field_conf['description'] : 0,
  );
  $form['fields']['typeName'] = array(
    '#type' => 'checkbox',
    '#title' => t('Dataset type'),  
    '#default_value' => isset($field_conf['type_name']) ? $field_conf['type_name'] : 0,
  );
  $form['fields']['organisationName'] = array(
    '#type' => 'checkbox',
    '#title' => t('Organisation name'),  
    '#default_value' => isset($field_conf['organisation_name']) ? $field_conf['organisation_name'] : 0,
  );
  $form['fields']['captureMethod'] = array(
    '#type' => 'checkbox',
    '#title' => t('Capture method'),  
    '#default_value' => isset($field_conf['capture_method']) ? $field_conf['capture_method'] : 0,
  );
  $form['fields']['purpose'] = array(
    '#type' => 'checkbox',
    '#title' => t('Purpose'),  
    '#default_value' => isset($field_conf['purpose']) ? $field_conf['purpose'] : 0,
  );
  $form['fields']['geographicalCoverage'] = array(
    '#type' => 'checkbox',
    '#title' => t('Geographical coverage'),  
    '#default_value' => isset($field_conf['geographical_coverage']) ? $field_conf['geographical_coverage'] : 0,
  );
  $form['fields']['quality'] = array(
    '#type' => 'checkbox',
    '#title' => t('Quality'),  
    '#default_value' => isset($field_conf['quality']) ? $field_conf['quality'] : 0,
  );
  $form['fields']['additionalInformation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Additinoal information'),  
    '#default_value' => isset($field_conf['additional_information']) ? $field_conf['additional_information'] : 0,
  );
  $form['fields']['accessConstraints'] = array(
    '#type' => 'checkbox',
    '#title' => t('Access constraints'),  
    '#default_value' => isset($field_conf['access_constraints']) ? $field_conf['access_constraints'] : 0,
  );
  $form['fields']['useConstraints'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use constraints'),  
    '#default_value' => isset($field_conf['use_constraints']) ? $field_conf['use_constraints'] : 0,
  );
  $form['fields']['temporalCoverage'] = array(
    '#type' => 'checkbox',
    '#title' => t('Temporal coverage'),  
    '#default_value' => isset($field_conf['temporal_coverage']) ? $field_conf['temporal_coverage'] : 0,
  );
  $form['fields']['updateFrequency'] = array(
    '#type' => 'checkbox',
    '#title' => t('Update frequency'),  
    '#default_value' => isset($field_conf['update_frequency']) ? $field_conf['update_frequency'] : 0,
  );
  $form['fields']['dateUploaded'] = array(
    '#type' => 'checkbox',
    '#title' => t('Date uploaded - numeric'),  
    '#default_value' => isset($field_conf['date_uploaded']) ? $field_conf['date_uploaded'] : 0,
  );
  $form['fields']['metadataLastEdited'] = array(
    '#type' => 'checkbox',
    '#title' => t('Date metadata last edited - numeric'),  
    '#default_value' => isset($field_conf['metadata_last_edited']) ? $field_conf['metadata_last_edited'] : 0,
  );
  $form['fields']['formattedDateUploaded'] = array(
    '#type' => 'checkbox',
    '#title' => t('Date uploaded - readable'),  
    '#default_value' => isset($field_conf['formatted_date_uploaded']) ? $field_conf['formatted_date_uploaded'] : 0,
  );
  $form['fields']['formatted_metadata_last_edited'] = array(
    '#type' => 'checkbox',
    '#title' => t('Date metadata last edited - readable'),  
    '#default_value' => isset($field_conf['formatted_metadata_last_edited']) ? $field_conf['formatted_metadata_last_edited'] : 0,
  );
  $form['fields']['organisationID'] = array(
    '#type' => 'checkbox',
    '#title' => t('Organisation id'),  
    '#default_value' => isset($field_conf['organisation_id']) ? $field_conf['organisation_id'] : 0,
  );
  $form['fields']['conditionsAccepted'] = array(
    '#type' => 'checkbox',
    '#title' => t('Conditions accepted'),  
    '#default_value' => isset($field_conf['conditions_accepted']) ? $field_conf['conditions_accepted'] : 0,
  );
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Output options')  
  );
  $form['options']['title_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display title as link to web page'),  
    '#default_value' => isset($option_conf['title_link']) ? $option_conf['title_link'] : 1,
  );
  $form['options']['format'] = array(
    '#type' => 'radios',
    '#title' => t('Ouput format'),  
    '#default_value' => isset($option_conf['format']) ? $option_conf['format'] : 'unformatted',
    '#options' => array(
        'unformatted' => t('Unformatted list'),
        'html_list' => t('Html list'),
        'table' => t('Table'),
    ),
  );
  $form['options']['wrapper_class'] = array(
    '#type' => 'textfield',
    '#title' => t('Wrapper class'),  
    '#description' => t('The css class of the outermost html element.'),
    '#default_value' => isset($option_conf['wrapper_class']) ? $option_conf['wrapper_class'] : '',
  );
  $form['options']['field_class'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add field classes'),  
    '#description' => t('Add css classes to each field.'),
    '#default_value' => isset($option_conf['field_class']) ? $option_conf['field_class'] : 1,
  );
  $form['options']['striping'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add striping classes'),  
    '#description' => t('Add css classes of odd and even for striping and first/last.'),
    '#default_value' => isset($option_conf['striping']) ? $option_conf['striping'] : 1,
  );
  return $form;
}

/**
* Submit function, note anything in the formstate[conf] automatically gets saved
*/
function nbn_organisation_datasets_edit_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $form_state['conf']['organisation'] = $values['organisation'];
  $form_state['conf']['type'] = $values['type'];
  $form_state['conf']['fields']['href'] = $values['href'];
  $form_state['conf']['fields']['organisationHref'] = $values['organisation_href'];
  $form_state['conf']['fields']['key'] = $values['key'];
  $form_state['conf']['fields']['title'] = $values['title'];
  $form_state['conf']['fields']['description'] = $values['description'];
  $form_state['conf']['fields']['typeName'] = $values['type_name'];
  $form_state['conf']['fields']['organisationName'] = $values['organisation_name'];
  $form_state['conf']['fields']['captureMethod'] = $values['capture_method'];
  $form_state['conf']['fields']['purpose'] = $values['purpose'];
  $form_state['conf']['fields']['geographicalCoverage'] = $values['geographical_coverage'];
  $form_state['conf']['fields']['quality'] = $values['quality'];
  $form_state['conf']['fields']['additionalInformation'] = $values['additional_information'];
  $form_state['conf']['fields']['accessConstraints'] = $values['access_constraints'];
  $form_state['conf']['fields']['useConstraints'] = $values['use_constraints'];
  $form_state['conf']['fields']['temporalCoverage'] = $values['temporal_coverage'];
  $form_state['conf']['fields']['updateFrequency'] = $values['update_frequency'];
  $form_state['conf']['fields']['dateUploaded'] = $values['date_uploaded'];
  $form_state['conf']['fields']['metadataLastEdited'] = $values['metadata_last_edited'];
  $form_state['conf']['fields']['formattedDateUploaded'] = $values['formatted_date_uploaded'];
  $form_state['conf']['fields']['formattedMetadataLastEdited'] = $values['formatted_metadata_last_edited'];
  $form_state['conf']['fields']['organisationID'] = $values['organisation_id'];
  $form_state['conf']['fields']['conditionsAccepted'] = $values['conditions_accepted'];
  $form_state['conf']['options']['title_link'] = $values['title_link'];
  $form_state['conf']['options']['format'] = $values['format'];
  $form_state['conf']['options']['wrapper_class'] = $values['wrapper_class'];
  $form_state['conf']['options']['field_class'] = $values['field_class'];
  $form_state['conf']['options']['striping'] = $values['striping'];
}

/**
* Run-time rendering of the body of the block (content type)
*/
function nbn_organisation_datasets_render($subtype, $conf, $args, $contexts) {
  module_load_include('inc', 'nbn', 'nbn_client');
  
  // Perform any substitutions from context in conf['organisation']
  $organisation = ctools_context_keyword_substitute($conf['organisation'], array(), $contexts);
  $organisation = intval($organisation);

  // Ensure organisation is a positive integer
  if (!is_int($organisation) || $organisation < 1) {
    // An incorrect substitution string resolves to '' but so does a correct
    // substitution string where no value is supplied. Therefore, it is not 
    // possible to report an error.
    return;
  }
  else {
    // Request data from NBN
    $nbn_client = new NBNClient;
    switch ($conf['type']) {
      case 'provided':
        $data = $nbn_client->GetOrganisationDatasets($organisation);
        break;
      case 'contributed':
        $data = $nbn_client->GetOrganisationContributedDatasets($organisation);
        break;
    }
  }
  
  // Ensure some data has been returned.
  if (empty($data)) {
    return;
  }
  else {
    // Theme data
    $variables = compact('data', 'conf');
    $variables['conf']['fields']['description'] = 1;    
    switch ($conf['options']['format']) {
      case 'table':
        $markup = theme('nbn_table', $variables);
        break;
      case 'html_list':
        $markup = theme('nbn_html_list', $variables);
        break;
      default:
        $markup = theme('nbn_unformatted', $variables);
        break;
    }

    // Save as render array
    $output = array(
        'para' => array(
            '#type' => 'markup',
            '#markup' => $markup,
        ),
    );
  }

  $block = new stdClass();
  $block->content = $output;
  return $block;
}

/**
 * 'admin info' callback for panel pane.
 */
function nbn_organisation_datasets_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    return $block;
  }
}
