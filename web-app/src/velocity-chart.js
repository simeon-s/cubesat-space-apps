import { LitElement, html } from "lit";

export class VelocityChart extends LitElement {
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
      return [new Date(`${d.date}T${d.time}`), d.speed];
    });
  }

  constructor() {
    super();

    this.data = [];
    this._rows = [];
    this._cols = [
      { label: "Time", type: "datetime" },
      { label: "Speed", type: "number" },
    ];
    this._options = {
      title: "Velocity over time",
      legend: { position: "none" },
      curveType: "function",
      vAxis: {
        title: "Speed (knots)",
        format: "# kn",
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
customElements.define("velocity-chart", VelocityChart);