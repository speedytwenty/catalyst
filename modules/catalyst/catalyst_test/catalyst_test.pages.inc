<?php

/**
 * @file
 */

function catalyst_test_basic() {
  if (empty($_GET['destination'])) {
    drupal_goto(current_path(), array('query' => drupal_get_destination()));
    drupal_exit();
  }
  catalyst_include('twig');
  $build = array();
  $lines = [];
  $vars = [];
  $lines[] = '<fieldset id="filters-tests" style="padding: 1em;"><legend>Twig Filters and Functions</legend>';
  //$lines[] = '<div id="test-t-function">{{ "t() is defined as a twig filter."|t }} and can be used {{ </div>';
  $vars['t_novar'] = 'Translated string without variable.';
  $lines[] = '<h3>Translation filter tests "t"</h3>';
  $lines[] = '<p><em>Used for text translation and string formatting.</em></p>';
  $lines[] = "<pre>{{ '{{ \"Translated string without variable.\"|t }}'|raw }}</pre>";
  $lines[] = '<p>{{ "Translated string without variable."|t }}</p>';
  $lines[] = "<pre>{{ '{{ \"Translated string with @variable.\"|t({\"@variable\": \"a variable.\"}}'|raw }}</pre>";
  $lines[] = '<p>{{ "Translated string with @variable."|t({"@variable": "a variable."}) }}</p>';
  $lines[] = '<h3>plural() function tests</h3>';
  $lines[] = '<p><em>Used for text translation and string formatting.</em></p>';
  $lines[] = "<pre>{{ '{{ \"Translated string with @variable.\"|t({\"@variable\": \"a variable.\"}}'|raw }}</pre>";
  $lines[] = "<pre>{{ '{{ plural(1, \"Singular string translated: @count\", \"Plural string translated: @count\") }}'|raw }}</pre>";
  $lines[] = '<pre>{{ plural(1, "Singular string translated: @count", "Plural string translated: @count") }}</pre>';
  $lines[] = "<pre>{{ '{{ plural(2, \"Singular string translated: @count\", \"Plural string translated: @count\") }}'|raw }}</pre>";
  $lines[] = '<pre>{{ plural(2, "Singular string translated: @count", "Plural string translated: @count") }}</pre>';
  $lines[] = '</legend>';

  $lines[] = '<fieldset id="link-tests" style="padding: 1em;"><legend>URLs and Links</legend>';
  $lines[] = '<h3>URL filter and function</h3>';
  $lines[] = '<pre>{{ "{{ url() }}"|raw }}</pre>';
  $lines[] = '<p>{{ url() }}</p>';
  $lines[] = '<pre>{{ "{{ url(current_path()) }}"|raw }}</pre>';
  $lines[] = '<p>{{ url(current_path()) }}</p>';
  $lines[] = '<pre> {{ "{{ current_path()|url({absolute: true, query: drupal_get_destination()}) }}"|raw }}</pre>';
  $lines[] = '<p>{{ current_path()|url({absolute: true, query: drupal_get_destination()}) }}</p>';
  $lines[] = '<h3>Link filter and function "l()"</h3>';

  $lines[] = "<pre>{{ '{{ l(\"Link text\", current_path()) }}'|raw }}' }}</pre>";
  $lines[] = '<p>{{ l("Link text", current_path()) }}</p>';

  $lines[] = "<pre>{{ '{{ \"Link text\"|l(current_path(), {query:drupal_get_destionation())  }}'|raw }}</pre>";
  $lines[] = '<p>{{ "Link text"|l(current_path(), {query:drupal_get_destination()}) }}</p>';
  $lines[] = '</fieldset>';

  $lines[] = '<div id="test-twig-alter">{{ custom_twig_function() }}</div>';

  $vars['render_test'] = array('#markup' => '<div id="render-test">Rendering is functioning.</div>');
  $lines[] = '{{ render_test|render }}';


  if (module_exists('block')) {
    $lines[] = '<h3>Core block function and filter tests</h3>';
    $lines[] = '<div id="block-test">'."{{ coreblock('system', 'powered-by') }}".'</div>';
    $lines[] = '<div id="block-test">'."{{ 'system'|coreblock('powered-by') }}".'</div>';
  }
  else $lines[] = '<p>Skipped block test as the block module is not enabled.</p>';
  $build['result'] = array('#markup' => catalyst_twig_render(implode("\n", $lines), $vars));
  return $build;

  // This doesn't work because twig doesn't pass references
  $vars['showme'] = array(
    'showmelater' => array('#markup' => '<p id="showmelater">Show me LATER</p>'),
    'showmenow' => array('#markup' => '<p id="showmenow">Show me NOW</p>'),
  );
  $lines[] = '{{ hide(showme.showmelater) }}';
  $lines[] = '{{ render(showme) }}';
  $lines[] = '{{ render(showme.showmelater) }}';
}
