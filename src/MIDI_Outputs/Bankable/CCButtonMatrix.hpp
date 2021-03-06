#pragma once

#include <Banks/BankAddresses.hpp>
#include <MIDI_Outputs/Bankable/Abstract/MIDIButtonMatrix.hpp>
#include <MIDI_Senders/DigitalCCSender.hpp>

BEGIN_CS_NAMESPACE

namespace Bankable {

/**
 * @brief   A class of MIDIOutputElement%s that read the input from a **matrix
 *          of momentary push buttons or switches**, and send out MIDI **Control
 *          Change** events.
 * 
 * A value of 0x7F is sent when a button is pressed, and a value of 0x00 is sent
 * when a button is released.  
 * Crude software debouncing is implemented by limiting the refresh rate.  
 * This version can be banked.
 *
 * @tparam  nb_rows
 *          The number of rows of the matrix.
 * @tparam  nb_cols
 *          The number of columns of the matrix.
 *
 * @ingroup BankableMIDIOutputElements
 */
template <uint8_t nb_rows, uint8_t nb_cols>
class CCButtonMatrix
    : public MIDIButtonMatrix<MatrixAddress<nb_rows, nb_cols>, DigitalCCSender,
                              nb_rows, nb_cols> {
  public:
    /**
     * @brief   Create a new Bankable CCButtonMatrix object with the given pins,
     *          controller numbers and channel.
     * 
     * @param   config
     *          The bank configuration to use: the bank to add this element to,
     *          and whether to change the address, channel or cable number.
     * @param   rowPins
     *          A list of pin numbers connected to the rows of the button
     *          matrix.  
     *          **⚠** These pins will be driven LOW as outputs (Lo-Z).
     * @param   colPins
     *          A list of pin numbers connected to the columns of the button
     *          matrix.  
     *          These pins will be used as inputs (Hi-Z), and the
     *          internal pull-up resistor will be enabled.
     * @param   controllers
     *          A 2-dimensional array of the same dimensions as the button
     *          matrix that contains the MIDI Controller number of each button.
     *          [0, 119]
     * @param   channelCN
     *          The MIDI channel [CHANNEL_1, CHANNEL_16] and Cable Number 
     *          [0, 15].
     * @param   sender
     *          The MIDI sender to use.
     */
    CCButtonMatrix(OutputBankConfig<> config, const PinList<nb_rows> &rowPins,
                   const PinList<nb_cols> &colPins,
                   const AddressMatrix<nb_rows, nb_cols> &controllers,
                   MIDIChannelCN channelCN, const DigitalCCSender &sender = {})
        : MIDIButtonMatrix<MatrixAddress<nb_rows, nb_cols>, DigitalCCSender,
                           nb_rows, nb_cols>{
              {config, controllers, channelCN}, rowPins, colPins, sender} {}
};

} // namespace Bankable

END_CS_NAMESPACE