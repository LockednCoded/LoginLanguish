import { GameState, ImageCaptchaStage, Stage } from "../scripts/cpp-bindings";

const CaptchaTile = ({
  source,
  onClick,
  selected,
}: {
  source: string;
  onClick: () => any;
  selected: boolean;
}) => {
  return (
    <div
      className={`relative transition-all ${
        selected ? "scale-95 border-blue-600 border-[5px]" : ""
      }`}
      onClick={onClick}
    >
      <div className="absolute bg-white opacity-0 transition-opacity duration-100 hover:opacity-50 w-full h-full" />
      <img src={source} alt="Image" className="w-full h-full aspect-square" />
    </div>
  );
};

export default function ImageCaptcha({
  gameState,
  updateFieldState,
  nextBtnClick,
}: {
  gameState: GameState;
  updateFieldState: (
    stage: Stage,
    fieldName: string,
    value: string
  ) => Promise<void>;
  nextBtnClick: () => Promise<void>;
}) {
  return (
    <div className="bg-opacity-25 bg-gray-950 fixed h-full w-full top-0 left-0 flex items-center justify-center">
      <div className="bg-white p-1">
        <div className="text-white bg-blue-600 p-3 mb-1">
          <h1 className="font-bold text-xl">
            {gameState.stages[ImageCaptchaStage].challengeText}
          </h1>
        </div>
        <div className="grid grid-cols-3 gap-1 w-[400px] h-[400px]">
          {gameState.stages[ImageCaptchaStage].images.map((image, i) => {
            return (
              <CaptchaTile
                source={image}
                onClick={() =>
                  updateFieldState(
                    ImageCaptchaStage,
                    "selectedImage",
                    i.toString()
                  )
                }
                selected={gameState.stages[
                  ImageCaptchaStage
                ].state.selected.includes(i)}
              />
            );
          })}
        </div>
        <div className="flex justify-end mt-1">
          <button
            className="bg-blue-600 text-lg text-white font-bold p-1 w-36"
            type="button"
            disabled={false}
            onClick={() => {
              nextBtnClick();
            }}
          >
            Verify
          </button>
        </div>
      </div>
    </div>
  );
}
