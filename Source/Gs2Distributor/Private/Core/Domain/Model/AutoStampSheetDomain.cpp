/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */


#include "Core/Domain/Model/AutoStampSheetDomain.h"

#include "Distributor/Gs2DistributorRestClient.h"
#include "Distributor/Result/CreateDistributorModelMasterResult.h"


namespace Gs2::Core::Domain::Model
{
    FAutoStampSheetDomain::FAutoStampSheetDomain(
        const Gs2::Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Net::Rest::FGs2RestSessionPtr Session,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const FString DistributorNamespaceName,
        const FString TransactionId,
        const FStampSheetConfigurationPtr StampSheetConfiguration
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        Session(Session),
        AccessToken(AccessToken),
        DistributorNamespaceName(DistributorNamespaceName),
        TransactionId(TransactionId),
        StampSheetConfiguration(StampSheetConfiguration)
    {
    }

    FAutoStampSheetDomain::FAutoStampSheetDomain(
        const FAutoStampSheetDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        Session(From.Session),
        AccessToken(From.AccessToken),
        DistributorNamespaceName(From.DistributorNamespaceName),
        TransactionId(From.TransactionId),
        StampSheetConfiguration(From.StampSheetConfiguration)
    {
    }

    FAutoStampSheetDomain::FRunTask::FRunTask(
            const TSharedPtr<FAutoStampSheetDomain> Self
    ): Self(Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAutoStampSheetDomain::FRunTask::Action(
        TSharedPtr<TSharedPtr<void*>> Result
    )
    {
        const auto Client = MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Self->Session);
        const auto Future = Client->GetStampSheetResult(
            MakeShared<Gs2::Distributor::Request::FGetStampSheetResultRequest>()
                ->WithNamespaceName(Self->DistributorNamespaceName)
                ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                ->WithTransactionId(Self->TransactionId)
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        const auto RunResult = Future->GetTask().Result();
        
        const auto StampSheetResult = RunResult->GetItem()->GetSheetResult();
        const auto StampTaskResults = RunResult->GetItem()->GetTaskResults();

        if (StampTaskResults != nullptr)
        {
            int Index = 0;
            for (auto StampTaskResult : *StampTaskResults)
            {
                const auto Action = (*RunResult->GetItem()->GetTaskRequests())[Index]->GetAction();
                const auto Request = (*RunResult->GetItem()->GetTaskRequests())[Index]->GetRequest();
                if (Action.IsSet() && Request.IsSet())
                {
                    Self->StampSheetConfiguration->StampTaskEventHandler(
                        *Action,
                        *Request,
                        StampTaskResult
                    );
                    Index++;
                }
            }
        }
        if (StampSheetResult.IsSet())
        {
            const auto Action = RunResult->GetItem()->GetSheetRequest()->GetAction();
            const auto Request = RunResult->GetItem()->GetSheetRequest()->GetRequest();
            if (Action.IsSet() && Request.IsSet())
            {
                Self->StampSheetConfiguration->StampSheetEventHandler(
                    *Action,
                    *Request,
                    *StampSheetResult
                );
            }
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAutoStampSheetDomain::FRunTask>> FAutoStampSheetDomain::Run()
    {
        return Gs2::Core::Util::New<FAsyncTask<FRunTask>>(this->AsShared());
    }
}
