
const NvCookies = {
  get(name) {
    const cookies = document.cookie.split('; ');
    for (let i = 0; i < cookies.length; i++) {
      const [key, value] = cookies[i].split('=');
      if (key === name) {
        return decodeURIComponent(value);
      }
    }
    return undefined; // Return undefined if the cookie doesn't exist
  },

  set(name, value, options = {}) {
    let cookieString = `${name}=${encodeURIComponent(value)}`;
    if (options.expires) {
      if (typeof options.expires === 'number') {
        const date = new Date();
        date.setTime(date.getTime() + options.expires * 24 * 60 * 60 * 1000);
        options.expires = date.toUTCString();
      }
      cookieString += `; expires=${options.expires}`;
    }
    if (options.path) {
      cookieString += `; path=${options.path}`;
    }
    if (options.domain) {
      cookieString += `; domain=${options.domain}`;
    }
    if (options.secure) {
      cookieString += '; secure';
    }
    document.cookie = cookieString;
  }
};


/* below Event listener checks the loaded in iframe hide the banner */
window.addEventListener('bannerLoaded', function otcustomcallback(){
    if(window.location !== window.parent.location) {
        document.getElementById('onetrust-consent-sdk').style.display='none';
    }    
	
	/* SEO header tags issue fix */
	var tagsH2 = document.querySelectorAll('#onetrust-consent-sdk h2');
	for (var i = 0; i < tagsH2.length; i++) { otwrap(tagsH2[i], "ot-h2"); }

	var tagsH3 = document.querySelectorAll('#onetrust-consent-sdk h3');
	for (var i = 0; i < tagsH3.length; i++) { otwrap(tagsH3[i], "ot-h3"); }

	var tagsH4 = document.querySelectorAll('#onetrust-consent-sdk h4');
	for (var i = 0; i < tagsH4.length; i++) { otwrap(tagsH4[i], "ot-h4"); }

	function otwrap(tag, otclass) {
		
		if (tag.parentElement && tag.parentElement.tagName.toLowerCase() === 'aside' && tag.parentElement.classList.contains(otclass)) {
			return; // Already wrapped, do nothing
		}
		
		var wrapper = document.createElement("aside");
		wrapper.classList.add(otclass);

		wrapper.style.display = "inline";

		// Copy the classList from the original tag
	   wrapper.classList.add(...tag.classList);

		// Insert the wrapper before the original element
		tag.parentNode.insertBefore(wrapper, tag);

		// Move the original element inside the wrapper
		wrapper.appendChild(tag);
	}	
	/* SEO header tags issue fix */
	
    const translations = {
        "en": { "done": "Done" },
        "en-us": { "done": "Done" },
        "zh-cn": {"done": "完成"},
        "zh-hans": {"done": "完成"},
        "zh-hant": {"done": "完成"},
		"zh-tw": { "done": "完成" },
        "ja-jp": { "done": "完了する" },
        "ja": { "done": "完了する" },
        "ko-kr": { "done": "완료" },
        "en-in": { "done": "Done" },
        "en-au": { "done": "Done" },
        "en-sg": { "done": "Done" },
        "id-id": { "done": "Selesai" },
        "th-th": { "done": "เสร็จสิ้น" },
        "vi-vn": { "done": "done" },
        "en-ph": { "done": "Done" },
        "en-my": { "done": "Done" },
        "en-gb": { "done": "Done" },
        "cs-cz": { "done": "Hotovo" },
        "da-dk": { "done": "Udført" },
        "de-de": { "done": "Fertig" },
        "es-es": { "done": "Hecho" },
        "fi-fi": { "done": "Valmis" },
        "fr-fr": { "done": "Terminé" },
        "it-it": { "done": "Fine" },
        "nb-no": { "done": "Ferdig" },
        "nl-nl": { "done": "Gereed" },
        "pl-pl": { "done": "Gotowe" },
        "ro-ro": { "done": "Gata" },
        "ru-ru": { "done": "Готово" },
        "sv-se": { "done": "Klart" },
        "tr-tr": { "done": "Bitti" },
        "fr-be": { "done": "Terminé" },
        "de-at": { "done": "Fertig" },
        "en-eu": { "done": "Done" },
        "en-me": { "done": "Done" },
        "es-la": { "done": "Listo" },
        "pt-br": { "done": "Concluído" }
    }

    const setNvDone = function () {
        var acceptbtn = document.getElementById('onetrust-accept-btn-handler');
        var rejectbtn = document.getElementById('onetrust-reject-all-handler');
		var btngroup = document.getElementById('onetrust-button-group');
		var isdoneBtn= document.getElementById('nv-done-btn-handler');		

        if(acceptbtn){
            acceptbtn.style.display = 'none';
        }
        if(rejectbtn){
            rejectbtn.style.display = 'none';
        }
        
		if(!isdoneBtn) {
			const lang = document.documentElement.lang.toLowerCase() || 'en';
			const doneButton = document.createElement('button');
			doneButton.id = 'nv-done-btn-handler';
			doneButton.textContent = translations[lang]?.done || translations['en'].done || 'Done';		
			if(btngroup) {
				document.getElementById('onetrust-button-group').appendChild(doneButton);      
			}		
		}
		const doneBtnevnt = document.getElementById('nv-done-btn-handler');
		doneBtnevnt.addEventListener('click', function () {
			OneTrust.Close();
		});
        
    };

	/* if gpc enabled then setting the Done button with translations */	
	function isGPCEnabled() {
   		return navigator.globalPrivacyControl === true;
    }

    if(isGPCEnabled() && !(OneTrust.IsAlertBoxClosed())) {
        setNvDone();
    }   

	// Function to parse query parameters from URL
	function getQueryParam(param) {
		const queryString = window.location.search;
		const urlParams = new URLSearchParams(queryString);
		return urlParams.get(param);
	}
	
	var manageCookiesLink = document.getElementById("manage-nvcookies-link");
	if(manageCookiesLink) {
		manageCookiesLink.addEventListener('click', function() {
			OneTrust.ToggleInfoDisplay();
		});
	}
	
	var showprefPanel = getQueryParam('manage-cookies');
	if(showprefPanel ==='true') {
		setTimeout(function(){
			OneTrust.ToggleInfoDisplay();
		},1000);		
	}		
	


	
	/* **************** */
	function isValidLoginDataAvailable(key) {
		try {
			const value = localStorage.getItem(key);
			if (value) {
				const item = JSON.parse(value);
				if (item.expiration) {
					const expirationDate = new Date(item.expiration);
					const currentDate = new Date();
					if (expirationDate > currentDate) {
						return item;
					} else {
						console.log('LocalStorage item has expired.');
						localStorage.removeItem(key);
						return null;
					}
				} else {
					console.log('LocalStorage item does not have an expiration date.');
					return item; // Or false, depending on your requirement
				}
			} else {
				return null;
			}
		} catch (e) {
			console.error('Error parsing localStorage item:', e);
			return null;
		}
	}
		
		
/* ************ */
		function preferenceGetRequest(url, headers) {	
			return new Promise((resolve, reject) => {
				$.ajax({
					url: url,
					method: 'GET',
					headers: headers,
					success: function(data) {
						resolve(data);
					},
					error: function(error) {
						reject(error);
					}
				});
			});
		}

/* ************ */

		function postPreferenceRequest(url, headers, data) {
			return new Promise((resolve, reject) => {
				$.ajax({
					url: url,
					method: 'PUT',
					headers: headers,
					data: JSON.stringify(data),
					xhrFields: {
						withCredentials: false 
					},
					crossDomain: true,
					contentType: 'application/json',
					success: function(data) {
						resolve(data);
					},
					error: function(error) {
						reject(error);
					}
				});
			});
		}

		function deleteDateProps(obj) {
		  if (obj) {
			['createAt', 'updatedAt', 'subscribedAt'].forEach(prop => {
			  if (prop in obj) {
				delete obj[prop];
			  }
			});
		  }
		}
/* ************ */
		function checkAndUpdateData() {           			
            const isOneTrustClosed = OneTrust.IsAlertBoxClosed();
			
			if(!isOneTrustClosed){
				const validLoginData = isValidLoginDataAvailable('acctFederationData');
				const gpcEnabled = isGPCEnabled();
				const isPrefUpdated = NvCookies.get('isPrefUpdated') ? NvCookies.get('isPrefUpdated') : false;
				if (validLoginData && gpcEnabled && isPrefUpdated !=="true") {
            	const url = 'https://api-prod.nvidia.com/services/preferences-service/api/v1/users/me/preferences';
				let headers = {
					'idtoken': validLoginData.id_token,
                    'access-token': validLoginData.access_token,
            		'X-Client': 'gpc'
                }
				preferenceGetRequest(url, headers)
                .then(function(data){
					console.log("Preference Data", data);
					
					if(data.gpcOverride=== null || data.gpcOverride === false) {
						if(OneTrust.GetDomainData().ConsentModel.Name==='opt-out'){
							var prefLoginGpc = document.getElementById('nv-pref-login-gpc-text');
							var prefLoginGpcOpted = document.getElementById('nv-pref-login-gpc-text-opted');
							var gpcText = document.getElementById('nv-gpc-text');
							
							if (!data.interestBasedAds) {
								data.interestBasedAds = { 'subscribed': false};
							}

							if (!data.targetedAdsOptIn) {
								data.targetedAdsOptIn = {'subscribed': false};
							}
							
							if(data.interestBasedAds.subscribed === true || data.targetedAdsOptIn.subscribed === true) {
								if (gpcText) gpcText.style.display = 'none';
								if (prefLoginGpcOpted) prefLoginGpcOpted.style.display = 'block';
							}else {
								if (gpcText) gpcText.style.display = 'none';
								if (prefLoginGpc) prefLoginGpc.style.display = 'block';
							}			
						}
						
                    	data.gpcOverride = true;
                        data.interestBasedAds.subscribed = false;
                        data.targetedAdsOptIn.subscribed = false;
						let areasOfInterests = data.areasOfInterest.map(area => area.machineName);
						data.areasOfInterest = areasOfInterests;			
						['developer', 'enterprise', 'startups', 'gaming'].forEach(key => {
						  deleteDateProps(data[key]);
						});						
                        console.log('Updated Data', data);
						postPreferenceRequest(url, headers, data)
                    	.then(function(res) {
							NvCookies.set('isPrefUpdated', true, "/");
							console.log('post pref response data', res);
                    	})
                        .catch(function(error){
							console.error("error", error);
						});
                    }

                })
                .catch(function(error){
					console.error("error", error);
                });

            }
			}
            
        }
	
	checkAndUpdateData();

	
	
},false);
/*
document.addEventListener("DOMContentLoaded", function() {
	
	function deleteCookie(name) {
    var domains = [
        '.www.nvidia.com',
        '.developer.nvidia.com',      
        '.nvidianews.nvidia.com',
		'.air.nvidia.com',
		'.www.nvidia.cn',
		'.forums.developer.nvidia.com'
    ];

    var path = '/'; 

    domains.forEach(function(domain) {
        document.cookie = name + "=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=" + path + "; domain=" + domain + ";";
    });
    
}
deleteCookie('OptanonConsent');
});*/




