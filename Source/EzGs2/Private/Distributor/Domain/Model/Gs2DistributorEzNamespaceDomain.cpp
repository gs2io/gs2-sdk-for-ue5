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

#include "Distributor/Domain/Model/Gs2DistributorEzNamespaceDomain.h"

namespace Gs2::UE5::Distributor::Domain::Model
{

    TOptional<FString> FEzNamespaceDomain::Status() const
    {
        return Domain->Status;
    }

    TOptional<FString> FEzNamespaceDomain::Result() const
    {
        return Domain->Result;
    }

    TOptional<FString> FEzNamespaceDomain::ContextStack() const
    {
        return Domain->ContextStack;
    }

    TOptional<int32> FEzNamespaceDomain::StatusCode() const
    {
        return Domain->StatusCode;
    }

    TSharedPtr<TArray<int32>> FEzNamespaceDomain::VerifyTaskResultCodes() const
    {
        return Domain->VerifyTaskResultCodes;
    }

    TSharedPtr<TArray<FString>> FEzNamespaceDomain::VerifyTaskResults() const
    {
        return Domain->VerifyTaskResults;
    }

    TSharedPtr<TArray<int32>> FEzNamespaceDomain::TaskResultCodes() const
    {
        return Domain->TaskResultCodes;
    }

    TSharedPtr<TArray<FString>> FEzNamespaceDomain::TaskResults() const
    {
        return Domain->TaskResults;
    }

    TOptional<int32> FEzNamespaceDomain::SheetResultCode() const
    {
        return Domain->SheetResultCode;
    }

    TOptional<FString> FEzNamespaceDomain::SheetResult() const
    {
        return Domain->SheetResult;
    }

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzBatchResultPayload>>> FEzNamespaceDomain::Results() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzBatchResultPayload>>>();
            for (auto Value : *Domain->Results) {
                Result->Add(
                    Gs2::UE5::Distributor::Model::FEzBatchResultPayload::FromModel(
                        Value
                    )
                );
            }
            return Result;
        }();
    }

    TOptional<FString> FEzNamespaceDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzNamespaceDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    FEzNamespaceDomain::FEzNamespaceDomain(
        Gs2::Distributor::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzNamespaceDomain::FBatchExecuteApiTask::FBatchExecuteApiTask(
        TSharedPtr<FEzNamespaceDomain> Self,
        TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzBatchRequestPayload>> RequestPayloads
    ): Self(Self), RequestPayloads(RequestPayloads)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzNamespaceDomain::FBatchExecuteApiTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Distributor::Domain::Model::FEzNamespaceDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->BatchExecuteApi(
                    MakeShared<Gs2::Distributor::Request::FBatchExecuteApiRequest>()
                        ->WithRequestPayloads([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Distributor::Model::FBatchRequestPayload>>>();
                            for (auto Value : RequestPayloads) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Distributor::Domain::Model::FEzNamespaceDomain>(
                    Task->GetTask().Result(),
                    Self->ConnectionValue
                );
                Task->EnsureCompletion();
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

    TSharedPtr<FAsyncTask<FEzNamespaceDomain::FBatchExecuteApiTask>> FEzNamespaceDomain::BatchExecuteApi(
        TArray<TSharedPtr<Gs2::UE5::Distributor::Model::FEzBatchRequestPayload>> RequestPayloads
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FBatchExecuteApiTask>>(
            this->AsShared(),
            RequestPayloads
        );
    }

    Gs2::UE5::Distributor::Domain::Iterator::FEzDescribeDistributorModelsIteratorPtr FEzNamespaceDomain::DistributorModels(
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Iterator::FEzDescribeDistributorModelsIterator>(
            Domain,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzNamespaceDomain::SubscribeDistributorModels(TFunction<void()> Callback)
    {
        return Domain->SubscribeDistributorModels(
            Callback
        );
    }

    void FEzNamespaceDomain::UnsubscribeDistributorModels(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeDistributorModels(
            CallbackId
        );
    }

    Gs2::UE5::Distributor::Domain::Model::FEzDistributorModelDomainPtr FEzNamespaceDomain::DistributorModel(
        const FString DistributorName
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Model::FEzDistributorModelDomain>(
            Domain->DistributorModel(
                DistributorName
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Distributor::Domain::Model::FEzUserDomainPtr FEzNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Model::FEzUserDomain>(
            Domain->User(
                UserId
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Distributor::Domain::Model::FEzUserGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Util::IGameSessionPtr GameSession
    ) const
    {
        return MakeShared<Gs2::UE5::Distributor::Domain::Model::FEzUserGameSessionDomain>(
            Domain->AccessToken(
                GameSession->AccessToken()
            ),
            GameSession,
            ConnectionValue
        );
    }
}
