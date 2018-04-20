console.log("I'm here");

var colorEnum = Object.freeze({"verycold":"#B1DBFF", "cold":"#5683FF", "average":"#AEFC60", "littlehot":"#FFFF4A", "hot":"#FC9032", "veryhot":"#FC4732"});
var temperature = 49;
var temperatureBody = $('#co_body_temperature');


$.get( "https://api.mlab.com/api/1/databases/testiot/collections/test?apiKey=vWIzv7LA8PHHlJvAIfFUcze6O0FubFEF", function( data ) {
    if ( console && console.log ) {
        data.forEach(function(element){
            $('#temp').append(element._id);
            //console.log(element)
        });
    }
});

temperatureBody.css("background-color", getColor(temperature));

function getColor(temperature){
    var color="#FFFFFF";
    if(temperature >=-10 && temperature <0){
        color = colorEnum.verycold;
    }else if(temperature >=0 && temperature <10){
        color = colorEnum.cold;
    }else if(temperature >=10 && temperature <20){
        color = colorEnum.average;
    }else if(temperature >=20 && temperature <30){
        color = colorEnum.littlehot;
    }else if(temperature >=30 && temperature <40){
        color = colorEnum.hot;
    }else if(temperature >=40 && temperature <50){
        color = colorEnum.veryhot;
    }
    return color;
}


