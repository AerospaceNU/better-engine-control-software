class ECSState:
    def __init__(self, name, list_of_redlines, config, failState="ONLINE_SAFE"):
        self.name = name
        self.list_of_redlines = list_of_redlines
        self.config = config
        self.fail_state = failState

    def __repr__(self):
        return str(self)

    def get_para_list(self):
        return f'("{self.name}", {self.list_of_redlines}, {self.config}, {self.fail_state})'

    def __str__(self):
        return f'ECSState{self.get_para_list()}'


# ECSState(std::string
# name, std::vector < IRedline * > & redlines, const
# CommandData & config, ECSState & failState);
#
# std::string
# name;
# std::vector < IRedline * > & redlines;
# CommandData
# config;
# ECSState & failState;