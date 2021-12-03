import { LitElement, html, css } from "lit";

import "@openlayers-elements/core/ol-map";
import "@openlayers-elements/maps/ol-control";
import "@openlayers-elements/maps/ol-layer-openstreetmap";
import "@openlayers-elements/maps/ol-layer-geojson";
import "@openlayers-elements/core/ol-layer-vector";
import "@openlayers-elements/maps/ol-marker-icon"

export class SatelliteLocation extends LitElement {
  static styles = [
    css`
      ol-map {
        height: 420px;
      }
    `,
  ];

  static get properties() {
    return { coordinates: { type: Array } };
  }

  constructor() {
    super();

    this.coordinates = [];
  }

  render() {
    const coordinates = this.coordinates || [];
    const lastCoordinate = coordinates[0];

    let center = {
      latitude: 0,
      longitude: 0,
    };

    if (lastCoordinate) {
      center = lastCoordinate;
    } else {
      return "";
    }

    return html`
      <ol-map zoom="16" .lat=${center.latitude} .lon=${center.longitude}>
        <ol-layer-openstreetmap>
          ${coordinates.map((coord, index) => {
            return html`
              <ol-layer-vector z-index="1">
                <ol-marker-icon
                  src="pin.png"
                  .id=${`Marker-${index}`}
                  .lat=${coord.latitude}
                  .lon=${coord.longitude}
                  anchor-y="38"
                  anchor-y-units="pixels"
                ></ol-marker-icon>
              </ol-layer-vector>
            `;
          })}
        </ol-layer-openstreetmap>
      </ol-map>
    `;
  }
}

customElements.define("satellite-location", SatelliteLocation);