<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Provider resources'),
  'description' => t('Given a provider id, returns resources'),
  'category' => t('NBN'),
  'edit form' => 'nbn_provider_resources_edit_form', // returns settings form for pane.
  'render callback' => 'nbn_provider_resources_render', // returns renderable content.
  'admin info' => 'nbn_provider_resources_admin_info', // returns information displayed on admin screen.
  'all contexts' => TRUE,
);

/**
* 'Edit form' callback for the content type.
*/
function nbn_provider_resources_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $field_conf = $form_state['conf']['fields'];
  $option_conf = $form_state['conf']['options'];
  $form['provider'] = array(
    '#type' => 'textfield',
    '#title' => t('NBN data provider id'),
    '#description' => t('You can determine the id of an organisation from its '
            . 'url at https://registry.nbnatlas.org/. Either insert a dp number'
            . 'or a %substitution token for a field.'),
    '#default_value' => isset($conf['provider']) ? $conf['provider'] : 'dp77',
  );
  $form['fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fields to display')  
  );
  // Field names match those in the NBN response
  $form['fields']['name'] = array(
    '#type' => 'checkbox',
    '#title' => t('Data resource name'),  
    '#default_value' => isset($field_conf['name']) ? $field_conf['name'] : 0,
  );
  $form['fields']['uri'] = array(
    '#type' => 'checkbox',
    '#title' => t('Uri of web service for the data resource'),  
    '#default_value' => isset($field_conf['uri']) ? $field_conf['uri'] : 0,
  );
  $form['fields']['uid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Unique id used publicly'),  
    '#default_value' => isset($field_conf['uid']) ? $field_conf['uid'] : 0,
  );
  $form['fields']['id'] = array(
    '#type' => 'checkbox',
    '#title' => t('Some other id'),  
    '#default_value' => isset($field_conf['id']) ? $field_conf['id'] : 0,
  );
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Output options')  
  );
  $form['options']['name_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display name as link to web page'),  
    '#default_value' => isset($option_conf['name_link']) ? $option_conf['name_link'] : 1,
  );
  $form['options']['link_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Base url of Atlas pages'),
    '#description' => t('Url to which uid will be appended in order to create link to data resource page.'),
    '#default_value' => isset($option_conf['link_url']) ? 
      $option_conf['link_url'] : 'https://registry.nbnatlas.org/public/show/',
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
function nbn_provider_resources_edit_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $form_state['conf']['provider'] = $values['provider'];
  $form_state['conf']['fields']['name'] = $values['name'];
  $form_state['conf']['fields']['uri'] = $values['uri'];
  $form_state['conf']['fields']['uid'] = $values['uid'];
  $form_state['conf']['fields']['id'] = $values['id'];
  $form_state['conf']['options']['name_link'] = $values['name_link'];
  $form_state['conf']['options']['link_url'] = $values['link_url'];
  $form_state['conf']['options']['format'] = $values['format'];
  $form_state['conf']['options']['wrapper_class'] = $values['wrapper_class'];
  $form_state['conf']['options']['field_class'] = $values['field_class'];
  $form_state['conf']['options']['striping'] = $values['striping'];
}

/**
* Run-time rendering of the body of the block (content type)
*/
function nbn_provider_resources_render($subtype, $conf, $args, $contexts) {
  module_load_include('inc', 'nbn', 'nbn_client');
  
  // Perform any substitutions from context in conf['provider']
  $provider = ctools_context_keyword_substitute($conf['provider'], array(), $contexts);

  // Ensure organisation is an integer with prefix dp
  $prov_prefix = substr($provider, 0, 2);
  $prov_int = substr($provider, 2);
  if ($prov_prefix !== 'dp' || !ctype_digit($prov_int)) {
    // An incorrect substitution string resolves to '' but so does a correct
    // substitution string where no value is supplied. Therefore, it is not 
    // possible to report an error.
    return;
  }
  else {
    // Request data from NBN
    $nbn_client = new NBNClient;
    $data = $nbn_client->GetProviderResources($provider);
  }
  
  // Ensure some data has been returned.
  if (empty($data)) {
    return;
  }
  else {
    // Theme data
    $variables = compact('data', 'conf');
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
function nbn_provider_resources_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : '';
    return $block;
  }
}
