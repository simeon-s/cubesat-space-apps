import { LitElement, html } from "lit";

export class GPSStatusChart extends LitElement {
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
      { id: "b", label: "Satellites linked", type: "number" },
      { id: "s", label: "GPS Quality", type: "number" },
    ];
    this._options = {
      title: "GPS Quality Status",
      // curveType: "function",
      legend: { position: "bottom" },
      bar: { groupWidth: '85%' },
      vAxis: {
        maxValue: 8,
        title: "Quality(0/1/2) and Satellites Count"
      }
    };
  }

  #data = [];
  get data() {
    return this.#data;
  }
  set data(d = []) {
    this.#data = d;
    this._rows = d.slice(0, 5).map((d) => {
      return [new Date(`${d.date}T${d.time}`), d.satellites, d.quality];
    });
  }

  render() {
    return html`
      <google-chart
        type="column"
        .options=${this._options}
        .cols=${this._cols}
        .rows=${this._rows}
      ></google-chart>
    `;
  }
}
customElements.define("gps-status-chart", GPSStatusChart);
