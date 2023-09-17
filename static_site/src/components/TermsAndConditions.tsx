import React from "react";
export default function TermsAndConditions({
  onRequestClose,
}: {
  onRequestClose: () => void;
}) {
  return (
    <div className="bg-gray-950/25 fixed h-full w-full top-0 left-0 flex items-center justify-center">
      <div className="bg-white p-1 h-[90%] w-[600px] rounded-md flex flex-col">
        <div className="flex justify-between p-4 align-top">
          <h2 className="text-xl">Terms and Conditions</h2>
          <button
            className="text-lg"
            type="button"
            onClick={onRequestClose}
            data-test-id="tsAndCs-close"
          >
            x
          </button>
        </div>
        <div className="overflow-y-scroll p-4 text-sm font-serif">
          Terms and Conditions for Generic Account Creation <br />
          <br />
          These Terms and Conditions ({'"'}Terms{'"'}) govern the use of the
          account creation and authentication login services ({'"'}Services{'"'}
          ) provided by Login Languish ({'"'}Company,{'"'} {'"'}We,{'"'} {'"'}
          Us,{'"'} or {'"'}Our{'"'}), as well as the participation in any
          associated games, applications, and platforms ({'"'}Games{'"'}). By
          creating a generic account and accessing the Services, you ({'"'}User,
          {'"'} {'"'}Player,{'"'} {'"'}You,{'"'} or {'"'}Your{'"'}) agree to be
          bound by these Terms. Please read these Terms carefully before
          proceeding.
          <br />
          <br />
          1. Account Creation:
          <br />
          <br />
          1.1. You must have been born on the summer solstice of 1984 to create
          an account and use the Services.
          <br />
          <br />
          1.2. You agree to provide accurate and complete information during the
          account creation process.
          <br />
          <br />
          1.3. You are solely responsible for maintaining the confidentiality of
          your account information, including your username and password.
          <br />
          <br />
          1.4. You agree to notify us immediately of any unauthorized use of
          your account or any other breach of security.
          <br />
          <br />
          1.5. Your password and username may be temporarily granted upon
          account creation for a 10-day period, during which they shall undergo
          rigorous inspection by the esteemed {'"'}Council of Cosmic Creativity.
          {'"'}
          This council, composed of a motley crew of pixel artisans, code
          sorcerers, and virtual philosophers, shall assess the harmony of your
          chosen username with the celestial tapestry of our digital realm.
          <br />
          <br />
          1.6. Should your password and username emerge unscathed from this
          celestial scrutiny, you shall be granted full access to your account.
          However, if the Council of Cosmic Creativity deems your chosen
          credentials to be lacking in spark, a virtual carrier pigeon shall be
          dispatched to guide you through the process of selecting a more
          harmonious identity.
          <br />
          <br />
          1.7. Please be advised that the cosmic council's decisions are final,
          and while appeals are not entertained, the virtual carrier pigeons are
          known to be particularly excellent listeners and can offer words of
          encouragement during your quest for the perfect username.
          <br />
          <br />
          2. Use of Services:
          <br />
          <br />
          2.1. The Services provided by the Company are for personal,
          non-commercial use only.
          <br />
          <br />
          2.2. You agree not to use the Services for any illegal, harmful,
          abusive, or unauthorized purposes. 2.3 Our services shall not under
          any circumstances be used for any of the following purposes: Salmon
          farming, interpretive dance rehearsals, attempts at time travel using
          household appliances, cheese production, goose wrangling, or launching
          rockets toward celestial bodies.
          <br />
          <br />
          2.4. You acknowledge and agree that the Company reserves the right to
          monitor and moderate your use of the Services.
          <br />
          <br />
          2.5. Our Services are occasionally monitored by a team of garden
          gnomes. You agree to handing over access to web-camera and microphone
          devices to allow gnomes to gauge whether you are complying with our
          terms of service.
          <br />
          <br />
          3. Content and Conduct:
          <br />
          <br />
          3.1. You are solely responsible for any content you create, upload, or
          share through the Services.
          <br />
          <br />
          3.2 You agree to be held responsible for any defamatory remarks made
          towards developers of “Login Languish” and may be subject to a trial
          by the CAPTCHA Tribunal. <br />
          <br />
          3.3. You agree not to engage in any behavior that violates the rights
          of others, including but not limited to copyright, trademark, or
          privacy rights.
          <br />
          <br />
          3.4. You agree not to use the Services to distribute, transmit, or
          display any content that is defamatory, obscene, or offensive.
          <br />
          <br />
          4. Intellectual Property:
          <br />
          <br />
          4.1. All content provided through the Services, including but not
          limited to graphics, text, audio, video, software, and trademarks, is
          owned by or licensed to the Company.
          <br />
          <br />
          4.2. You may not reproduce, modify, distribute, or otherwise exploit
          any content from the Services without prior written consent from the
          Company. Doing so will result in bad things. <br />
          <br />
          5. Termination:
          <br />
          <br />
          5.1. The Company reserves the right to suspend or terminate your
          account, or restrict your access to the Services, at its sole
          discretion and without notice. You may also have your birth
          certificate confiscated if password and username criteria are not met.
          <br />
          <br />
          5.2. You may terminate your account at any time by following the
          instructions provided in the Services.
          <br />
          <br />
          6. Disclaimer of Warranty:
          <br />
          <br />
          6.1. The Services are provided {'"'}as is{'"'} and {'"'}as available,
          {'"'} without any warranties of any kind, either express or implied.
          <br />
          <br />
          6.2. The Company does not guarantee the accuracy, reliability, or
          completeness of any content provided through the Services. <br />
          <br />
          7. Limitation of Liability:
          <br />
          <br />
          7.1. To the extent permitted by law, the Company shall not be liable
          for any direct, indirect, incidental, consequential, or punitive
          damages arising out of or in connection with your use of the Services.
          <br />
          <br />
          7.2. In no event shall the total liability of the Company exceed the
          amount paid by you, if any, for the use of the Services.
          <br />
          <br />
          7.3. The Company will not pay for replacement of devices due to
          excessive button mashing or keyboard pounding during intense gameplay.
          <br />
          <br />
          8. Governing Law:
          <br />
          <br />
          8.1. These Terms shall be governed by and construed in accordance with
          the laws of [Your Country/State], without regard to its conflict of
          law principles.
          <br />
          <br />
          9. Changes to Terms:
          <br />
          <br />
          9.1. The Company reserves the right to update or modify these Terms at
          any time without prior notice.
          <br />
          <br />
          9.2. Continued use of the Services after any changes to the Terms
          constitutes your acceptance of the modified Terms.
          <br />
          <br />
          By creating an account and accessing the Services, you acknowledge
          that you have read, understood, and agree to abide by these Terms and
          Conditions. If you do not agree to these Terms, you may not use the
          Services.
          <br />
          <br />
          Last updated: 10/08/2023 For any questions or concerns regarding these
          Terms, please contact your internet provider.
        </div>
      </div>
    </div>
  );
}
