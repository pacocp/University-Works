<?php



$max = $argv[1];
$done = false;
while(!$done){
    $numbers = range(0, $max);
    shuffle($numbers);
    $done = true;
    foreach($numbers as $key => $val){
        if($key == $val){
            $done = false;
            break;
        }
    }
}

 
$arr = $numbers;

$sortedArr = bubbleSort($arr);


function bubbleSort( array &$array )
{
	do
	{
		$swapped = false;
		for( $i = 0, $c = count( $array ) - 1; $i < $c; $i++ )
		{
			if( $array[$i] > $array[$i + 1] )
			{
				list( $array[$i + 1], $array[$i] ) =
						array( $array[$i], $array[$i + 1] );
				$swapped = true;
			}
		}
	}
	while( $swapped );
}

?>