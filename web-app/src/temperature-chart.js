import { LitElement, html } from "lit";

export class TemperatureChart extends LitElement {
  static properties = {
    data: { type: Array },
    _rows: { state: true, type: Array },
    _cols: { state: true, type: Array },
    _options: { state: true, type: Object },
  };

  #data = [];
  get data() {
    return this.#data;
  }
  set data(d = []) {
    this.#data = d;
    this._rows = this.data.map((d) => {
      return [new Date(`${d.date}T${d.time}`), d.temp];
    });
  }

  constructor() {
    super();

    this.data = [];
    this._rows = [];
    this._cols = [
      { label: "Time", type: "datetime" },
      { label: "Temperature", type: "number" },
    ];
    this._options = {
      title: "Temperature over time",
      legend: { position: "none" },
      vAxis: {
        format: "# ℃",
      },
    };
  }

  render() {
    return html`
      <google-chart
        type="line"
        .options=${this._options}
        .cols=${this._cols}
        .rows=${this._rows}
      ></google-chart>
    `;
  }
}
customElements.define("temperature-chart", TemperatureChart);
