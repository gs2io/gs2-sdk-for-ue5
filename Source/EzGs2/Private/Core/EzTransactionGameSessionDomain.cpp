#include "Core/EzTransactionGameSessionDomain.h"

namespace Gs2::UE5::Core::Domain
{
	FEzTransactionGameSessionDomain::FEzTransactionGameSessionDomain(
		Gs2::Core::Domain::FTransactionAccessTokenDomainPtr Domain,
		Gs2::UE5::Util::FGs2ConnectionPtr& ConnectionValue
	):
		Domain(Domain),
		ConnectionValue(ConnectionValue)
	{
	}

	FEzTransactionGameSessionDomain::FWaitTask::FWaitTask(
	    TSharedPtr<FEzTransactionGameSessionDomain> Self,
        bool All
	):
        Self(Self),
        All(All)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FEzTransactionGameSessionDomain::FWaitTask::Action(
		TSharedPtr<TSharedPtr<FEzTransactionGameSessionDomain>> Result
	)
	{
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Wait(All);
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<FEzTransactionGameSessionDomain>(
                	Task->GetTask().Result(),
                	Self->ConnectionValue
                );
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
	}

	TSharedPtr<FAsyncTask<FEzTransactionGameSessionDomain::FWaitTask>> FEzTransactionGameSessionDomain::Wait(
		bool All
	)
	{
		return Gs2::Core::Util::New<FAsyncTask<FWaitTask>>(
			this->AsShared(),
			All
		);
	}
}