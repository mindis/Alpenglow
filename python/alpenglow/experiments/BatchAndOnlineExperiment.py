import alpenglow.Getter as rs
import alpenglow as prs


class BatchAndOnlineExperiment(prs.OnlineExperiment):
    def config(self, elems):
        config = self.parameter_defaults(
            top_k=100,
            min_time=0,
            loggers=[],
        )

        model = rs.FactorModel(**self.parameter_defaults(
            begin_min=-0.01,
            begin_max=0.01,
            dimension=10,
            initialize_all=False,
        ))

        #
        # batch
        #

        # updater
        batch_updater = rs.FactorModelGradientUpdater(
            learning_rate=self.parameter_default('batch_learning_rate', 0.05),
            regularization_rate=0.0
        )
        batch_updater.set_model(model)

        # negative sample generator
        batch_negative_sample_generator = rs.UniformNegativeSampleGenerator(**self.parameter_defaults(
            negative_rate=self.parameter_default('batch_negative_rate', 70),
            initialize_all=False,
        ))

        # objective
        point_wise = rs.ObjectiveMSE()
        batch_gradient_computer = rs.GradientComputerPointWise()
        batch_gradient_computer.set_objective(point_wise)
        batch_gradient_computer.set_model(model)

        # learner
        batch_learner = rs.OfflineImplicitGradientLearner(**self.parameter_defaults(
            number_of_iterations=9,
            start_time=-1,
            period_length=86400,
            write_model=False,
            read_model=False,
            clear_model=False,
            learn=True,
            base_out_file_name="",
            base_in_file_name=""
        ))
        batch_learner.set_model(model)
        batch_learner.add_gradient_updater(batch_updater)
        batch_learner.set_gradient_computer(batch_gradient_computer)
        batch_learner.set_negative_sample_generator(batch_negative_sample_generator)

        #
        # online
        #

        # updater
        online_updater = rs.FactorModelGradientUpdater(
            learning_rate=self.parameter_default('online_learning_rate', 0.2),
            regularization_rate=0.0
        )
        online_updater.set_model(model)

        # negative sample generator
        online_negative_sample_generator = rs.UniformNegativeSampleGenerator(**self.parameter_defaults(
            negative_rate=self.parameter_default('online_negative_rate', 100),
            initialize_all=False,
        ))

        # objective
        point_wise = rs.ObjectiveMSE()
        online_gradient_computer = rs.GradientComputerPointWise()
        online_gradient_computer.set_objective(point_wise)
        online_gradient_computer.set_model(model)

        # learner
        online_learner = rs.ImplicitGradientLearner()
        online_learner.add_gradient_updater(online_updater)
        online_learner.set_model(model)
        online_learner.set_negative_sample_generator(online_negative_sample_generator)
        online_learner.set_gradient_computer(online_gradient_computer)

        learner = [batch_learner, online_learner]

        return {
            'config': config,
            'model': model,
            'learner': learner
        }
