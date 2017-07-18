"""RTTLib library for converting RTTL to Arduino tone library notes."""


def RTTLnotes(melody):
    """Split raw string into list of invididual RTTL notes."""
    noteslist = melody.split(sep=",")
    return noteslist


def duration_function(duration_default, note):
    """The duration_function extracts the Arduino tone library duration from a
    single RTTL note.

    The function has two arguments, a single RTTL note (string) and default
    note duration (int) in the standard notation (2, 4, 8, 16, 32), and
    returns a note duration (int) in milliseconds.

    func(int, string) -> int
    """
    # create list to compare standard durations
    note_durations = ['2', '4', '8', '16', '32', '64']

    # extract duration and convert to type int
    if note[:2] in note_durations:
        correct_duration = note[:2]
        correct_duration = int(correct_duration)

    elif note[0] in note_durations:
        correct_duration = note[0]
        correct_duration = int(correct_duration)

    else:
        correct_duration = int(duration_default)

    # return int with correct duration in milliseconds.
    # can change back to normal scale by returning only correct_duration
    return int(1000/correct_duration)


def scale_function(note):
    """The scale_function extracts the Arduino tone library scale from a
    single RTTL note.

    The function has one argument, a single RTTL note (string), and returns
    the proper scale (string) for the Arduino tone-library.

    func(string) -> string
    """
    # create list to compare scales
    note_scale = ['a', 'b', 'c', 'd', 'e', 'f', 'g']

    # extract scale
    if note[0] in note_scale:
        correct_scale = note[0]

    elif note[1] in note_scale:
        correct_scale = note[1]

    else:
        correct_scale = note[2]

    # return string with correct scale as upper case
    return correct_scale.upper()


def octave_function(octave_default, note):
    """
    The octave_function extracts the Arduino tone library octave from a single
    RTTL note.

    The function has two arguments, a single RTTL note (string) and octave
    default value (int), and returns the proper octave (string) for the Arduino
    tone-library.

    func (int, string) -> string
    """
    # create empty string to collect potential octave elements
    octave_region = ''

    # create list to compare scales and octaves
    note_scale = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
    octave_scale = ['0', '1', '2', '3', '4', '5', '6', '7', '8']

    # return default octave if single note ('e', 'f.')
    if len(note) == 1:
        return str(octave_default)

    # return correct octave if two element note ('6b', 'a#', 'a7',)
    if len(note) == 2:
        if note[1] in octave_scale:
            return note[1]
        else:
            return str(octave_default)

    # extract note elements past scale ('a#.', 8a#', '2f6, 8f6, 16f.6, 16f#.6')
    for i in note:
        if i in note_scale:
            past_scale = note.index(i) + 1
            octave_region = note[past_scale:]
            break
        else:
            pass

    # if octave scale present, return its value
    for j in octave_region:
        if j in octave_scale:
            return j
        else:
            pass

    # return string with default octave
    return str(octave_default)


def RTTLconv(duration, octave, melody):
    '''
    The RTTLconv function converts RTTL notes into Arduino tone library notes.

    The function has three arguments; the default note duration (int) in the
    standard notation (2, 4, 8, 16, 32), the octave default value (int), and
    the RTTL melody (raw string). The return value is a list containing two
    strings, the first string contains notes separated by commas, and the
    second string contains the note durations (in milliseconds) separated by
    commas. Both strings are compatible with the Arduino tone-library.

    func(int, int, raw string) -> list[string, string]
    '''
    # split raw string into list of invididual notes
    notes = RTTLnotes(melody)

    # create empty list to hold tone strings and duration
    tones = []
    durations = []

    # create blank string for each note.
    # read each position and add in correct part (build new string)
    for note in notes:
        # set dotted note flag to default False.
        dotted_note = False

        # check if a pause (p) note is present.
        if 'p' in note:
            # set no_pause flag
            no_pause = False

            # set scale and duration
            correct_scale = 'PAUSE'
            sharp = ''
            correct_octave = ''
            correct_duration = duration_function(duration, note[0])

            # Combine note elements into pause tone string (NOTE_PAUSE).
            tone_string = 'NOTE_' + correct_scale + sharp + correct_octave
            tones.append(tone_string)
            durations.append(correct_duration)

        else:
            # set no_pause flag
            no_pause = True

            # extract correct duration -- func(int, string) -> int
            correct_duration = duration_function(duration, note)

            # extract correct note scale -- func(string) -> string
            correct_scale = scale_function(note)

            # extract octave from note -- func (int, string) -> string
            correct_octave = octave_function(octave, note)

            # extract sharp if present
            sharp = ''
            for i in note:
                if i == '#':
                    sharp = 'S'
                    break
                else:
                    pass

            # detect dotted note.
            for i in note:
                if i == '.':
                    # since dot is before octave (i.e. 16g#.6), the second note
                    # is half duration. after note is 1.5x duration.
                    second_duration = (correct_duration*0.5)
                    second_duration = int(second_duration)
                    dotted_note = True
                    break
                else:
                    pass

            # Combine note elements into tone string (NOTE_CS5).
            # Ensure dotted note comes after full note
            if no_pause and dotted_note:
                tone_string = 'NOTE_' + correct_scale + sharp + correct_octave
                second_tone = 'NOTE_' + correct_scale + sharp + correct_octave
                tones.append(tone_string)
                tones.append(second_tone)
                durations.append(correct_duration)
                durations.append(second_duration)
            else:
                tone_string = 'NOTE_' + correct_scale + sharp + correct_octave
                tones.append(tone_string)
                durations.append(correct_duration)

    # print out length of completted notes.
    # original input did not include dotted notes!!!
    print('The number of notes in this melody is: ', len(tones))

    # ensure tones are returned as a properly formatted string
    separator = ', '
    tones_astuple = tuple(tones)
    formatted_tones = ''
    for i in tones_astuple:
        formatted_tones += (i + separator)

    # ensure durations are returned as a properly formatted string
    durations_astuple = tuple(durations)
    formatted_durations = ''
    for j in durations_astuple:
        formatted_durations += (str(j) + separator)

    # return Arduino tone library notes and durations as strings
    return [formatted_tones[:-2], formatted_durations[:-2]]


class RTTL():
    """The RTTL class allows RTTL raw string objects to be manipulated.

    RTTL, or Ring Tone Transfer Language, is commonly used to encode simple
    melodies into cellphone ring tones. This class allows these melodies to
    be converted into Arduion tone library compatible data objects encoding
    the proper scale and note durations.
    """
    def __init__(self, rttlr, duration=0, octave=0):
        """Creates an instance of RTTL class.

        RTTL takes a string that represents the RTTL melody. To be used when we
        convert from RTTL to Arduino Tone Library.

        :param rttlr: represents the RTTL melody.
        :type rttlr: raw string
        :param duration: (optional) default note duration.
        :type duration: int, default=0
        :param octave: (optional) default octave.
        :type octave: int, default=0.
        """
        self.rttlr = rttlr
        self.duration = duration
        self.octave = octave
        self.rttlp = RTTLnotes(rttlr)

    def __repr__(self):
        return self.rttlr

    def __str__(self):
        return ','.join(self.rttlp)

    def set_duration(self, duration):
        """Sets the default duration."""
        self.duration = duration

    def set_octave(self, octave):
        """Sets the default octave."""
        self.octave = octave

    def octave(self, note):
        """Returns the octave from given RTTL note."""
        return octave_function(self.octave, note)

    def scale(self, note):
        """Returns the scale from a given RTTL note."""
        return scale_function(note)

    def duration(self, note):
        """Returns the duration from a given RTTL note."""
        return duration_function(self.duration, note)

    def RTTL2Tone(self):
        """Converts RTTL melody to Arduino Tone Library format. Returns a list
        with each notes scale and duration as strings.
        """
        return RTTLconv(self.duration, self.octave, self.rttlr)
