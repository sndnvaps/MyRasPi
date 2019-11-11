<?php
$mysqli = new mysqli("173.10.0.2", "root", "5XSwBxGx", "Temps");

/* check connection */
if (mysqli_connect_errno()) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
}

$data=array();
class Alteration{
    public $temp;
    public $humi;
    public $update_time;
}

//set timezone +8:00
$mysqli->query("SET time_zone = '+8:00'");

$query = "SELECT temp,humi,update_time FROM pi_temps";

if ($stmt = $mysqli->prepare($query)) {

    /* execute statement */
    $stmt->execute();

    /* bind result variables */
    $stmt->bind_result($temp, $humi, $update_time);

    /* fetch values */
    while ($stmt->fetch()) {
       // printf ("%s (%s)\n", $temp, $humi, $update_time);
        $alter = new Alteration();
        $alter->temp = $temp;
        $alter->humi = $humi;
        $alter->update_time = $update_time;
        $data[] = $alter;
    }

    /* close statement */
    $stmt->close();
}

echo json_encode($data);

/* close connection */
$mysqli->close();
?>
