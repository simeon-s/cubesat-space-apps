import { LitElement, html } from "lit";

export class AnglesChart extends LitElement {
  static properties = {
    data: { type: Array },
    _rows: { state: true, type: Array },
    _cols: { state: true, type: Array },
    _options: { state: true, type: Object },
  };

  constructor() {
    super();

    this.data = [];
    this._rows = [];
    this._cols = [
      { label: "Time", type: "datetime" },
      { label: "x", type: "number" },
      { label: "y", type: "number" },
      { label: "z", type: "number" },
    ];
    this._options = {
      title: "Satellite angles of orientation",
      legend: { position: "bottom" },
      curveType: "function",
      vAxis: {
        title: "Angle",
      }
    };
  }

  #data = [];
  get data() {
    return this.#data;
  }
  set data(d = []) {
    this.#data = d;
    this._rows = d.map((d) => {
      return [new Date(`${d.date}T${d.time}`), d.x, d.y, d.z];
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
customElements.define("angles-chart", AnglesChart);
