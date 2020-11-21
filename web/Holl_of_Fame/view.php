<?php
error_reporting(0);
include 'flag.php'; # <- flag

if(isset($_GET['img'])){
	$ext = explode(".", $_GET['img']);
	$ext = $ext[sizeof($ext)-1];
	
	if(!preg_match("/png|jpg/i", $ext)) exit("no hack");
	
	if(isset($_POST['length'])){
                $length = $_POST['length'];
	}	
	else{
		$length = strlen($_GET['img']);
	}

	$image = substr($_GET['img'], 0, $length);
	$view = fopen("./image/".$image, 'rb');

	header("Content-Type: image/png");
	fpassthru($view);
}
else {
	echo "Pwnhyo's Image Viewer";
}

if(isset($_GET['view-source'])){
    	highlight_file(__FILE__);
}
?>
