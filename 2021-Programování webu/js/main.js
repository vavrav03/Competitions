// changes header background color on scrolling
window.addEventListener("scroll", function () {
   let header = $("header");
   if( window.scrollY > 0){
      header.addClass("header-scrolling-active");
   } else {
      header.removeClass("header-scrolling-active");
   }
});

// Redirects people to the buy tickets page from all buttons with tickets class
const ticketButtons = $(".tickets");
for (const ticketButton of ticketButtons) {
   $(ticketButton).click((e) => {
      location.href = "https://unsplash.com/images/animals/kitten";
   });
}

//Changes color of the newsletter button and deletes input
const newsletterButton = $("#newsletter-button");
const message = newsletterButton.find("span");
const emailInput = newsletterButton.parent().find(".email-input");
newsletterButton.click((e) => {
   newsletterButton.addClass("newsletter-clicked");
   message.text("Děkujeme");
   setTimeout((e) => {
      newsletterButton.removeClass("newsletter-clicked");
      message.text("Odebírat newsletter");
      emailInput.val("");
   }, 5000);
});

//Displays more information about the event
const displayMoreButton = $("#display-more-about-event");
displayMoreButton.click((e) => {
   const displayMoreButtonSpan = displayMoreButton.find("span");
   const collapsed = displayMoreButtonSpan.text() === "Více informací";
   $("#first-section .more-info-text").slideToggle("medium");
   console.log(collapsed)
   if (collapsed) {
      displayMoreButton.html(
         '<span>Méně informací</span><img class="svg-icon svg-icon-white" src="OBRÁZKY/arrow-up-solid.svg" />'
      );
   } else {
      displayMoreButton.html(
         '<span>Více informací</span><img class="svg-icon svg-icon-white" src="OBRÁZKY/arrow-down-solid.svg" />'
      );
   }
});

//Displays other artists
const displayAllButton = $("#display-all");
displayAllButton.click((e) => {
   const displayAllButtonSpan = displayAllButton.find("span");
   const collapsed = displayAllButtonSpan.text() === "Zobrazit vše";
   $(".card.to-toggle").slideToggle("medium", function () {
      if ($(this).is(":visible")) {
         $(this).css("display", "flex");
      }
   });
   if (collapsed) {
      displayAllButton.html(
         '<span>Zobrazit méně</span><img class="svg-icon svg-icon-black" src="OBRÁZKY/arrow-up-solid.svg" />'
      );
   } else {
      displayAllButton.html(
         '<span>Zobrazit vše</span><img class="svg-icon svg-icon-black" src="OBRÁZKY/arrow-down-solid.svg" />'
      );
   }
});

//Displays more info about the artist 
$(".more-info").click(function () {
   const card = $(this).parent().parent();
   const name = $(card).find(".name");
   $(name).slideToggle("medium");
   const moreInfoText = $(card).find(".more-info-text");
   $(moreInfoText).slideToggle("more-info-text");
   const backgroundImage = $(card).css("background-image");
   const backgroundImageUrl = backgroundImage.split("url")[1];
   if(backgroundImage.split("rgba(0, 0, 0, ")[1].startsWith("0.3")){
      $(card).css(
         "background-image",
         `linear-gradient(0deg, rgba(0, 0, 0, 0.8), rgba(0, 0, 0, 0.8)), url${backgroundImageUrl}`
      );
   } else {
      $(card).css(
         "background-image",
         `linear-gradient(0deg, rgba(0, 0, 0, 0.3), rgba(0, 0, 0, 0.3)), url${backgroundImageUrl}`
      );
   }
});

$('#header-toggler').click(function(e){
   const header = $("header");
   const nav = $(header).find("nav");
   if($(nav).hasClass("responsive")){
      header.addClass("header-scrolling-active");
      nav.removeClass("responsive");
   } else {
      header.removeClass("header-scrolling-active");
      nav.addClass("responsive");
   }
});