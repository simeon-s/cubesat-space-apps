import { LitElement, html, css } from "lit";
import "@google-web-components/google-chart";

import "./temperature-chart";
import "./angles-chart";
import "./battery-chart";
import "./velocity-chart";
import "./altitude-chart";
import "./gps-status-chart"
import "./satellite-location";

export class SpaceApp extends LitElement {
    static properties = {
        _data: { state: true, type: Array },
        _coordinates: { state: true, type: Array },
    };

    static get styles() {
        return css `
      :host {
        display: block;
        padding: 16px;
        max-width: 960px;
        margin: 0 auto;
      }

      :host h1 {
        text-align: center;
        font-family: system-ui;
      }

      :host .charts-container {
        display: flex;
        flex-wrap: wrap;
        justify-content: center;
      }

      :host .map-container {
        margin-top: 2rem;
      }
    `;
    }

    constructor() {
        super();

        this._data = [];
        this._coordinates = [];
    }

    async connectedCallback() {
        super.connectedCallback();

        try {

            // Note: build with json file src
            const data = await fetch(
                "https://cube-sat.000webhostapp.com/json_req.php"
            ).then((res) => res.json());

            this._data = data;
            this._coordinates = data.map((d) => ({
                latitude: dmstodeg(d.latitude),
                longitude: dmstodeg(d.longitude),
            }));
            console.table(this._coordinates);
        } catch (error) {
            console.error("could not load data", error);
        }
    }
    
    // todo request data and refresh charts
    async connectedCallback() {
      super.connectedCallback();
  
      this.loadData();
      setInterval(() => {
        this.loadData();
      }, 10000); // every 10 sec
    }
  
    async loadData() {
      try {
        // Note: build with json file src
        const data = await fetch(
          "https://cube-sat.000webhostapp.com/json_req.php"
        ).then((res) => res.json());
  
        this._data = data;
        this._coordinates = data.map((d) => ({
          latitude: dmstodeg(d.latitude),
          longitude: dmstodeg(d.longitude),
        }));
      } catch (error) {
        console.error("could not load data", error);
      }
    }

    render() {
        return html `
      <h1>SpaceSense - Space Apps 2021</h1>

      <div class="charts-container">
        <temperature-chart .data=${this._data}></temperature-chart>
        <angles-chart .data=${this._data}></angles-chart>
        <battery-chart .data=${this._data}></battery-chart>
        <velocity-chart .data=${this._data}></velocity-chart>
        <altitude-chart .data=${this._data}></altitude-chart>
        <gps-status-chart .data=${this._data}></gps-status-chart>
      </div>
      <div class="map-container">
        <satellite-location
          .coordinates=${this._coordinates}
        ></satellite-location>
      </div>
    `;
    }
}

function dmstodeg(dms) {
  let min = Math.trunc(dms) % 100;
  let deg = Math.trunc(dms / 100);
  let sec = (dms % 1) * 60;
  return deg + min/60 + sec/(60*60);
}

customElements.define("space-app", SpaceApp);