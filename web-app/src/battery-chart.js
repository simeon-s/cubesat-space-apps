import { LitElement, html } from "lit";

export class BatteryChart extends LitElement {
  static properties = {
    data: { type: Array },
    _rows: { state: true, type: Array },
    _cols: { state: true, type: Array },
    _options: { state: true, type: Object },
  };

  constructor() {
    super();

    this._rows = [];
    this._cols = [
      { id: "t", label: "Time", type: "datetime" },
      { id: "b", label: "Battery", type: "number" },
      { id: "s", label: "Solar panel", type: "number"},
    ];
    this._options = {
      title: "Electrical power system",
      curveType: "function",
      legend: { position: "bottom" },
      vAxis: {
        title: "Voltage",
        format: "# V",
      },
    };
  }

  #data = [];
  get data() {
    return this.#data;
  }
  set data(d = []) {
    this.#data = d;
    this._rows = d.map((d) => {
      return [new Date(`${d.date}T${d.time}`), d.bv, d.pv];
    });
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
customElements.define("battery-chart", BatteryChart);
