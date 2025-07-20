require 'voronoi-rb/extension'
require 'raylib'

class TestApp
  def run
    inputs = [
      [0.25,0.25], [0.75,0.75], [0.10, 0.4], [0.3, 0.9],
      [0.1, 0.1], [0.9, 0.9], [0.1, 0.9]
    ]
    array = Voronoi::Diagram.generate(inputs)
    Raylib.load_lib('libraylib')
    Raylib.InitWindow(800, 640, 'Hello world')
    Raylib.SetTargetFPS(60)

    until Raylib.WindowShouldClose()
      Raylib.BeginDrawing
      Raylib.ClearBackground(Raylib::RAYWHITE)

      inputs.each { |point|
        Raylib.DrawCircle(point[0]*800, point[1]*640, 2, Raylib::BLACK)
      }
      array.each { |edge|
        Raylib.DrawLine(edge[0]*800, edge[1]*640, edge[2]*800, edge[3]*640, Raylib::BLACK)
      }

      Raylib.EndDrawing
    end

    Raylib.CloseWindow
  end
end

TestApp.new.run

