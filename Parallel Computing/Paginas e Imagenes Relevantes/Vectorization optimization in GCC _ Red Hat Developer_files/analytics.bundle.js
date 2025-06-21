(function () {
  try {
    const AWS_GATEWAY_URL =
      "https://qr9wo7otse.execute-api.us-west-2.amazonaws.com/Prod";
    const API_URL = `${AWS_GATEWAY_URL}/v1/analytics`;
    const href = window.document.location.href;

    const REQUESTS_LIMIT = 60;
    const DEFAULT_DURATION = 5;
    const ANALYTIC_INITIAL_DURATION = 5000;

    let publicKey;
    let analyticCreation;
    let counter = 0;
    window.addEventListener("beforeunload", stopCreateAnalytics);

    init();

    function checkForCurrentScript() {
      const currentScript =
        document.currentScript ||
        document.querySelectorAll("script[ll-public-key]")[0];
      return {
        currentScript: currentScript,
        currentScriptIsPresent: !!currentScript,
      };
    }

    async function init() {
      const { currentScript, currentScriptIsPresent, domain } =
        checkForCurrentScript();

      if (!currentScriptIsPresent) {
        return;
      }

      publicKey = currentScript.getAttribute("ll-public-key") || "";

      analyticCreation = function timeoutPromise(
        publicKey,
        checkHref,
        uuid = "",
      ) {
        return new Promise((reject) => {
          window.setTimeout(
            createAnalytic,
            ANALYTIC_INITIAL_DURATION,
            publicKey,
            checkHref,
            uuid,
          );
        });
      };

      if (!isBotDetected()) {
        await analyticCreation(publicKey, false);
      }
    }

    function isBotDetected() {
      const googleBotPattern =
        "(googlebot/|bot|APIs-Google|Mediapartners-Google|AdsBot-Google-Mobile|AdsBot-Google-Mobile|\n" +
        "AdsBot-Google|Googlebot-Image|Googlebot|Googlebot-News|Googlebot-Video|Mediapartners-Google|\n" +
        "AdsBot-Google-Mobile-Apps|FeedFetcher-Google|Google-Read-Aloud|DuplexWeb-Google|Google Favicon|googleweblight)";
      const regexp = new RegExp(googleBotPattern, "i");
      return regexp.test(navigator.userAgent);
    }

    async function createAnalytic(publicKey, checkHref, uuid = "") {
      if (
        (checkHref && href !== window.document.location.href) ||
        counter >= REQUESTS_LIMIT
      ) {
        uuid = "";
        stopCreateAnalytics();
        return null;
      }

      counter++;

      try {
        const response = await fetch(API_URL, {
          method: "POST",
          body: JSON.stringify({
            public_key: publicKey,
            url: href,
            duration: DEFAULT_DURATION.toString(),
            uuid: uuid,
            counter: counter,
            ll_auction: "",
          }),
          headers: {
            "Content-Type": "application/json",
          },
        });

        if (!response.ok) {
          uuid = "";
          stopCreateAnalytics();
          throw new Error(
            `Loop API ${response.status} Error: POST request to analytics`,
          );
        }

        const json = await response.json();

        if (json["uuid"]) {
          analyticCreation = function timeoutPromise(
            publicKey,
            checkHref,
            uuid = "",
          ) {
            return new Promise((reject) => {
              window.setTimeout(
                createAnalytic,
                ANALYTIC_INITIAL_DURATION,
                publicKey,
                checkHref,
                uuid,
              );
            });
          };
          await analyticCreation(publicKey, true, json["uuid"]);
        }
      } catch (error) {
        uuid = "";
        stopCreateAnalytics();
        console.warn(error);
      }
    }

    function stopCreateAnalytics() {
      clearTimeout(analyticCreation);
    }
  } catch (error) {
    console.warn(error);
  }
})();
