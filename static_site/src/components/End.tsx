import React from "react";
import ConfettiExplosion from "react-confetti-explosion";
export default function End() {
  return (
    <main className="flex flex-col justify-center w-full h-full bg-white rounded-sm select-none">
      <div className="overflow-y-scroll">
        <div className="py-14 flex flex-col items-center box-border">
          <ConfettiExplosion
            force={1.8}
            duration={3000}
            particleCount={400}
            width={1000}
          />
          <h1 className="text-2xl m-0">The End.</h1>
          <h1 className="text-m m-0">Thanks for playing Login Languish!</h1>
        </div>
      </div>
    </main>
  );
}
