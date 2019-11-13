<?php
//http://rpi_ip/getrecord.php?search=all
//http://rpi_ip/getrecord.php?search=one
//http://rpi_pi/getrecord.php?search=hour
if (isset($_GET['search']) && is_string($_GET['search'])) {
    $search = (string) $_GET['search'];
    if (strcmp($search,"all") == 0) {
             $is_search_all = true;
    } else if (strcmp($search, "one") == 0) {
              $is_search_all = false;
    } else if (strcmp($search, 'hour') == 0) {
              $is_search_hour = true;
    } else {
              $is_search_one = true;
    }
}

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
//get one record && all the record
if ($is_search_all) {
    $query = "SELECT temp,humi,update_time FROM pi_temps";
} else if ($is_search_one) {
    $query = "SELECT temp,humi,update_time FROM pi_temps where id= (SELECT MAX(id) FROM pi_temps)";
} else  if ($is_search_hour) {
    $query = "SELECT temp,humi,update_time FROM pi_temps where substring(update_time,15,2)='00'";
} else {
    $query = "SELECT temp,humi,update_time FROM pi_temps where id= (SELECT MAX(id) FROM pi_temps)";
}
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
