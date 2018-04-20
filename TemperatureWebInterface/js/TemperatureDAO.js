function formatDate(date) {
    var maDate = date.split(" ")[0];
    maDate = maDate.split('-');

    var mydate = new Date(maDate[0], maDate[1] - 1, maDate[2]);

    var options = { weekday: 'long', year: 'numeric', month: 'long', day: 'numeric' };

    return mydate.toLocaleDateString('fr-FR', options);
}

function  TemperatureDAO() {
    this.getAllTemperatureData = function(){
        var dataToReturn = [];
        $.get( "https://api.mlab.com/api/1/databases/testiot/collections/test?apiKey=vWIzv7LA8PHHlJvAIfFUcze6O0FubFEF", function( data ) {
            if ( console && console.log ) {

                data.forEach(function(element){
                    if(element.idRaspberry == 1){
                        dataToReturn.push({"date" : formatDate(element.date), "id" : element.idRaspberry, "temperature" : element.temperature});
                    }

                });
                console.log(dataToReturn);
                $.get('../template/temperature.html',
                    function(response) {
                        var templateHtml = $(response).filter('#temperature').html();
                        div = document.createElement("div");
                        console.log(div)
                        div.innerHTML = Mustache.render(templateHtml, {message : dataToReturn});
                        console.log(div)
                        document.getElementById('model').appendChild(div);


                    });
            }
        });
    };


}
