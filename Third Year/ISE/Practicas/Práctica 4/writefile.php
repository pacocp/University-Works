<?php

$filename = $argv[1];
$myfile = fopen($filename, "w") or die("Unable to open file!");
for( $i = 0; $i < 1000000; $i++ )
{
  fwrite($myfile, $i);
}

fclose($myfile);
?>
