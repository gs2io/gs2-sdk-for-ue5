#include "Core/EzTransactionDomain.h"

namespace Gs2::UE5::Core::Domain
{
	FEzTransactionDomain::FEzTransactionDomain(
		Gs2::Core::Domain::FTransactionDomainPtr Domain,
		Gs2::UE5::Util::FGs2ConnectionPtr& ConnectionValue
	):
		Domain(Domain),
		ConnectionValue(ConnectionValue)
	{
	}

	FEzTransactionDomain::FWaitTask::FWaitTask(
	    TSharedPtr<FEzTransactionDomain> Self,
        bool All
	):
        Self(Self),
        All(All)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FEzTransactionDomain::FWaitTask::Action(
		TSharedPtr<TSharedPtr<FEzTransactionDomain>> Result
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
                *Result = MakeShared<FEzTransactionDomain>(
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

	TSharedPtr<FAsyncTask<FEzTransactionDomain::FWaitTask>> FEzTransactionDomain::Wait(
		bool All
	)
	{
		return Gs2::Core::Util::New<FAsyncTask<FWaitTask>>(
			this->AsShared(),
			All
		);
	}
}