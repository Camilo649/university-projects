jQuery(function($) {
  if (typeof window.nodWidgets !== 'undefined') {
    function nvdLogin() {
      window.location = '/login';
    }

    function nvLogout() {
    }

    function getJWTToken() {
      return localStorage.getItem('STYXKEY_nv_jwt');
    }

    function isCNSite() {
      return location.origin.endsWith('.cn');
    }

    function initNodWidgets() {
      var roles = '';
      var searchJwtToken = '';

      if (typeof Cookies.get("nv.profile") !== "undefined") {
        var nvProfile = JSON.parse(decodeURI(atob(Cookies.get("nv.profile"))));
        searchJwtToken = nvProfile["jwtToken"];
        roles = nvProfile["nv.program"];
      }

      NvidiaGalleryWidget.unmountAll();

      var searchInput1 = {
        query: '-',
        maxResults: 12,
      };

      var site = 'https://www.nvidia.com';
      var destinationSite = 'https://www.nvidia.com';
      var lang = 'en-us';
      var jwt = '';
      var facets = 'event_sessionIndustry, mimetype';

      const styxkey = getJWTToken();
      if (styxkey) {
        jwt = styxkey;
      }

      for (var i = 0; i < window.nodWidgets.length; i++) {
        var widget = window.nodWidgets[i];
        var id = widget.id;
        var destination = widget.destination;
        var sessionIndustries = widget.sessionIndustries;
        var header = widget.header;
        var type = widget.type;
        var playlistId = widget.playlistId;

        if (typeof widget.header === 'undefined') {
          header = '';
        }

        if (typeof widget.type === 'undefined') {
          type = 'facet';
        }

        var options = {
          elementId: id,
          searchInput: searchInput1,
          site: site,
          destinationSite: destinationSite,
          destination: destination,
          language: lang,
          jwtToken: jwt,
          isFeatured: false,
          isFeaturedPlaylist: false,
          searchToken: searchJwtToken,
          accessRoles: roles,
          header: header,
          onLogin: () => { nvdLogin(); },
          onLogout: () => { nvLogout(); },
          apiUrl: 'https://api-prod.nvidia.com/search/graphql',
          voltronApiUrl: 'https://api-prod.nvidia.com/services/nod/api/v1/'
        };

        let isCnSite = false;
        // @TODO Add CN site detection.

        if (isCnSite) {
          options.apiUrl = 'https://api-prod.nvidia.cn/search/graphql';
          options.voltronApiUrl = 'https://api-prod.nvidia.cn/services/nod/api/v1/';
        }

        if (type === 'playlist') {
          options.playlistId = playlistId;
        } else {
          options.facets = facets;
          options.facetFilters = {
            event_sessionIndustry: sessionIndustries,
            mimetype: ['event session']
          };
        }

        NvidiaGalleryWidget.mount(options);
      }
    }

    const styxkey = getJWTToken();
    if (styxkey !== null) {
      var nvIdToken = styxkey;
      var createKalturaSessionUrl = 'https://api-prod.nvidia.com/nod/api/v1/kaltura/session/create';
      if (isCNSite()) {
        createKalturaSessionUrl = 'https://api-prod.nvidia.cn/nod/api/v1/kaltura/session/create';
      }

      jQuery.ajax({
        url: createKalturaSessionUrl,
        headers: { "Authorization": 'Bearer ' + nvIdToken },
        xhrFields: {
          withCredentials: true
        }
      }).always(function() {
        initNodWidgets();
      });
    } else {
      if (typeof Cookies.get("nv.profile") !== "undefined") {
        var deleteKalturaSessionUrl = 'https://api-prod.nvidia.com/nod/api/v1/kaltura/session/delete';
        if (isCNSite()) {
          deleteKalturaSessionUrl = 'https://api-prod.nvidia.cn/nod/api/v1/kaltura/session/delete';
        }

        jQuery.ajax({
          url: deleteKalturaSessionUrl,
          xhrFields: {
            withCredentials: true
          }
        }).always(function() {
          initNodWidgets();
        });
      } else {
        initNodWidgets();
      }
    }
  }
});
