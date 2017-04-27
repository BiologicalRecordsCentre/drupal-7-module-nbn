<?php

/**
 * @file
 * Template to display an nbn response in an unformatted list.
 *
 * - $data : An array containing selected data from the NBN indexed by row 
 * or an error.
 * - $wrapper_classes: Classes to apply to the container
 * - $row_classes: An array of classes to apply to each row, indexed by row
 * number. This matches the index in $data.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id */
?>

<?php if (!isset($data)): ?>
  <div <?php if ($wrapper_classes) { print 'class="' . $wrapper_classes . '" '; } ?>> 
    <h3>
      <?php t("There was an error communicating with the NBN Gateway.") ?>
    </h3>
      <?php t("No error message available.") ?>
    </p>
  </div>

<?php elseif (array_key_exists('error', $data)): ?>
  <div <?php if ($wrapper_classes) { print 'class="' . $wrapper_classes . '" '; } ?>> 
    <h3>
      <?php t("There was an error communicating with the NBN Gateway.") ?>
    </h3>
    <p><?php print t($data['error']) ?></p>
  </div>

<?php else: ?>
  
  <div <?php if ($wrapper_classes) { print 'class="' . $wrapper_classes . '" '; } ?>> 
  <?php foreach($data as $row_count => $row): ?>
    <div <?php if ($row_classes[$row_count]) { print 'class="' . $row_classes[$row_count] .'"';  } ?>>
    <?php foreach($row as $field_name => $content): ?>
      <div <?php if (!empty($field_classes[$field_name])) { print 'class="' . $field_classes[$field_name] . '" '; } ?>>
        <?php print $content ?>
      </div>
    <?php endforeach ?>
    </div>
  <?php endforeach ?>
  </div>  
  
<?php endif ?>
  
