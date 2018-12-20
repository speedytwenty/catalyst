<h2>Region Block Tests</h2>
<h3 id="region-block">This is a block placed into a region via the block itself.</h3>
<h3>Region Block CSS Tests</h3>
<ul><li class="block-custom-css-test">This should have a <strong>solid</strong> border.</li>
  <li class="block-shared-css-test">This should have a <strong>double</strong> border.</li>
  <li class="block-remote-css-test">This should have a <strong>dotted</strong> border.</li>
  <li class="block-local-css-test">This should have a <strong>dashed</strong> border.</li>
</ul><script>
<!--//--><![CDATA[// ><!--

  QUnit.test("Region Block CSS Tests", function (assert) {
    assert.equal(jQuery('.block-custom-css-test').css('border-top-style'), 'solid', 'Region Block Custom CSS Test');
    assert.equal(jQuery('.block-shared-css-test').css('border-top-style'), 'double', 'Region Block Shared CSS Test');
    assert.equal(jQuery('.block-local-css-test').css('border-top-style'), 'dashed', 'Region Block Local CSS Test');
    assert.equal(jQuery('.block-remote-css-test').css('border-top-style'), 'dotted', 'Region Block Remote CSS Test');
  });

//--><!]]>
</script><h3>Region Block Files Tests</h3>
<strong>Custom file test:</strong>
<ul><li>Test <em>custom</em> file PATH: <strong>/sites/dev-catalyst.dd/files/media/block/%5Bfield__machine%5D/block-custom-test_3.png</strong></li>
  <li>Test <em>custom</em> file URL: <strong>public://media/block/[field__machine]/block-custom-test_3.png</strong></li>
  <li>Test <em>custom</em> file as image:<br /><img id="block-custom-file-test" src="/sites/dev-catalyst.dd/files/media/block/%5Bfield__machine%5D/block-custom-test_3.png" /></li>
</ul><strong>Shared file test:</strong>
<ul><li>Test <em>shared</em> file PATH: <strong></strong></li>
  <li>Test <em>shared</em> file URL: <strong></strong></li>
  <li>Test <em>shared</em> file as image:<br /><img id="block-shared-file-test" src="" /></li>
</ul><strong>Local file test:</strong>
<ul><li>Test <em>local</em> file PATH: <strong></strong></li>
  <li>Test <em>local</em> file URL: <strong></strong></li>
  <li>Test <em>local</em> file as image:<br /><img id="block-local-file-test" src="" /></li>
</ul><strong>Remote file test:</strong>
<ul><li>Test <em>remote</em> file PATH: <strong></strong></li>
  <li>Test <em>remote</em> file URL: <strong></strong></li>
  <li>Test <em>remote</em> file as image:<br /><img id="block-remote-file-test" src="" /></li>
</ul><script>
<!--//--><![CDATA[// ><!--

QUnit.test("Region Block Tests", function (assert) {
  assert.ok('', 'Block "title" variable Test');
  assert.equal('', 'region block var val', 'Region Block Processing Test');
});  
QUnit.test("Region Block Javascript Tests", function (assert) {
  assert.notEqual(typeof block_custom_js_var, 'undefined', 'Region Block Custom Javascript Test');
  assert.notEqual(typeof block_shared_js_var, 'undefined', 'Region Block Shared Javascript Test');
  assert.notEqual(typeof block_remote_js_var, 'undefined', 'Region Block Remote Javascript Test');
  assert.notEqual(typeof block_local_js_var, 'undefined', 'Region Block Local Javascript Test');
  assert.notEqual(typeof block_footer_js_var, 'undefined', 'Region Block Footer Javascript Test');
});
QUnit.test("Region Block Files Tests", function (assert) {
  var blockCustomFileImg = jQuery('img#block-custom-file-test');
  assert.ok(blockCustomFileImg.attr('src'), 'Region Block Custom File Data Test');
  assert.equal(blockCustomFileImg.width(), 403, 'Region Block Custom File Exists Test');
  var blockSharedFileImg = jQuery('img#block-shared-file-test');
  assert.ok(blockSharedFileImg.attr('src'), 'Region Block Shared File Data Test');
  assert.equal(blockSharedFileImg.width(), 303, 'Region Block Shared File Exists Test');
  var blockLocalFileImg = jQuery('img#block-local-file-test');
  assert.ok(blockLocalFileImg.attr('src'), 'Region Block Local File Data Test');
  assert.equal(blockLocalFileImg.width(), 203, 'Region Block Local File Exists Test');
  var blockRemoteFileImg = jQuery('img#block-remote-file-test');
  assert.ok(blockRemoteFileImg.attr('src'), 'Region Block Remote File Data Test');
  assert.equal(blockRemoteFileImg.width(), 103, 'Region Block Remote File Exists Test');
});

//--><!]]>
</script>