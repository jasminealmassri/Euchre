document.addEventListener('DOMContentLoaded', function(){
    let card5 = document.querySelector('.player1_hand .card:nth-child(5)');
    let card5_img = document.querySelector('.player1_hand .card:nth-child(5) img');

    card5.onclick = function() {
        card5_img.style.width = '14vh';
        card5_img.style.height = 'auto';
        card5.style.transform = 'translate(-135%, -120%)';
    }

});