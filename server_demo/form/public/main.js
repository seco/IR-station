function getWifiList(){
	console.log("Getting wifi list")
	$.getJSON(
		'/wifiList',
		{},
		function(data) {
			$.each(data,function(index,wifi){
				$('#wifiList').append($('<option>').val(wifi).text(wifi));
			});
			$('#info-status').text("Loading successful.")
			$('#form').toggle();
			$('#ap').toggle();
		}
	).fail(function(){
			$('#info-status').text('Connection Failed. Please Reload.');
	});
}
function form(){
	if(confirm("Are you sure to confirm?")){
		$('#form').toggle();
		$('#ap').toggle();
		$('#info-status').text("Connecting... Please wait.");
		$.get('/confirm',{
			ssid: $('#form [name="ssid"]').val(),
			password: $('#form input[name="password"]').val(),
			url: $('#form input[name="url"]').val()
		}).done(function(res){
			if(res=="false"){
				$('#form').toggle();
				$('#ap').toggle();
				$('#info-status').text("Connection failed. Please try again.");
			}else{
				$('#info-status').html('Connection Successful.<br/>Please make a note of this URL: <a href="http:\/\/' + res + '/">http://' + res + '/</a>');
				$('button.reboot').show();
			}
		});
	}
}
function setAP(){
	if(confirm("Can I setup as Access Point Mode?")){
		$('#form').toggle();
		$('#ap').toggle();
		$('#info-status').text("Connecting... Please wait.");
		$.get('/accessPointMode',{
			url: $('#ap input[name="url"]').val()
		}).done(function(res){
			$('#info-status').text(res);
		});
	}
}

$('#form button').click(form);
$('#form input').keypress(function(e){
	if(e.which == 13){
		form();
	}
});

$('#ap button').click(setAP);
$('#ap input').keypress(function(e){
	if(e.which == 13){
		setAP();
	}
});

$('button.reboot').click(function(e){
	$.get('/reboot');
});
getWifiList();

