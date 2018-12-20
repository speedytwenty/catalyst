<h1>Template tests:</h1>
<div id="template-test">
  <div id="template-label"><label>Label:</label><span><a href="/admin/catalyst/doctype/?destination=devel/php"></a> ()</span></div>
  <div id="template-label"><label>Machine:</label><span></span></div>
  <div id="template-content">
    
  </div>
</div>
<script>
  QUnit.test("Template tests", function (assert) {
    assert.ok($('#template-content').html(), 'Template has output.');
    assert.equal(jQuery('#template-test').css('border-top-style'), 'dashed', 'Template custom CSS is functioning.');
    assert.equal('', '1', 'Template preprocessing is functioning.');
    assert.equal('', 'catalyst_test_1x', 'Template is attached to the catalyst_test_1x package.');
    assert.equal(template_test_custom_js, 1, 'Template custom javascript is functioning.');
  });
</script>