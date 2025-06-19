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

#include "SkillTree/Domain/Model/Gs2SkillTreeEzStatusGameSessionDomain.h"

namespace Gs2::UE5::SkillTree::Domain::Model
{

    TOptional<FString> FEzStatusGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzStatusGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzStatusGameSessionDomain::PropertyId() const
    {
        return Domain->PropertyId;
    }

    FEzStatusGameSessionDomain::FEzStatusGameSessionDomain(
        Gs2::SkillTree::Domain::Model::FStatusAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzStatusGameSessionDomain::FReleaseTask::FReleaseTask(
        TSharedPtr<FEzStatusGameSessionDomain> Self,
        TArray<FString> NodeModelNames
    ): Self(Self), NodeModelNames(NodeModelNames)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStatusGameSessionDomain::FReleaseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Release(
                    MakeShared<Gs2::SkillTree::Request::FReleaseRequest>()
                        ->WithNodeModelNames([&]{
                            auto Arr = MakeShared<TArray<FString>>();
                            for (auto Value : NodeModelNames) {
                                Arr->Add(Value);
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
                *Result = MakeShared<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzStatusGameSessionDomain::FReleaseTask>> FEzStatusGameSessionDomain::Release(
        TArray<FString> NodeModelNames
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FReleaseTask>>(
            this->AsShared(),
            NodeModelNames
        );
    }

    FEzStatusGameSessionDomain::FRestrainTask::FRestrainTask(
        TSharedPtr<FEzStatusGameSessionDomain> Self,
        TArray<FString> NodeModelNames
    ): Self(Self), NodeModelNames(NodeModelNames)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStatusGameSessionDomain::FRestrainTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Restrain(
                    MakeShared<Gs2::SkillTree::Request::FRestrainRequest>()
                        ->WithNodeModelNames([&]{
                            auto Arr = MakeShared<TArray<FString>>();
                            for (auto Value : NodeModelNames) {
                                Arr->Add(Value);
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
                *Result = MakeShared<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzStatusGameSessionDomain::FRestrainTask>> FEzStatusGameSessionDomain::Restrain(
        TArray<FString> NodeModelNames
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FRestrainTask>>(
            this->AsShared(),
            NodeModelNames
        );
    }

    FEzStatusGameSessionDomain::FResetTask::FResetTask(
        TSharedPtr<FEzStatusGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStatusGameSessionDomain::FResetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Reset(
                    MakeShared<Gs2::SkillTree::Request::FResetRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Core::Domain::FEzTransactionGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzStatusGameSessionDomain::FResetTask>> FEzStatusGameSessionDomain::Reset(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FResetTask>>(
            this->AsShared()
        );
    }

    FEzStatusGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzStatusGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzStatusGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::SkillTree::Model::FEzStatusPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::SkillTree::Model::FEzStatus::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzStatusGameSessionDomain::FModelTask>> FEzStatusGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzStatusGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::SkillTree::Model::FEzStatusPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::SkillTree::Model::FStatusPtr Item)
            {
                Callback(Gs2::UE5::SkillTree::Model::FEzStatus::FromModel(Item));
            }
        );
    }

    void FEzStatusGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
