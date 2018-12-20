<?php

function catalyst_get_bundles($name = NULL) {
  catalyst_include('plugins');
  return catalyst_get_plugins('bundle', $name);
}
