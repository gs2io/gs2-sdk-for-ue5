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

#include "Version/Domain/Model/Gs2VersionEzAcceptVersionGameSessionDomain.h"

namespace Gs2::UE5::Version::Domain::Model
{

    TOptional<FString> FEzAcceptVersionGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzAcceptVersionGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzAcceptVersionGameSessionDomain::VersionName() const
    {
        return Domain->VersionName;
    }

    FEzAcceptVersionGameSessionDomain::FEzAcceptVersionGameSessionDomain(
        Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzAcceptVersionGameSessionDomain::FAcceptTask::FAcceptTask(
        TSharedPtr<FEzAcceptVersionGameSessionDomain> Self,
        Gs2::UE5::Version::Model::FEzVersionPtr Version
    ): Self(Self), Version(Version)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAcceptVersionGameSessionDomain::FAcceptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Accept(
                    MakeShared<Gs2::Version::Request::FAcceptRequest>()
                        ->WithVersion(Version == nullptr ? nullptr : Version->ToModel())
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
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

    TSharedPtr<FAsyncTask<FEzAcceptVersionGameSessionDomain::FAcceptTask>> FEzAcceptVersionGameSessionDomain::Accept(
        Gs2::UE5::Version::Model::FEzVersionPtr Version
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptTask>>(
            this->AsShared(),
            Version
        );
    }

    FEzAcceptVersionGameSessionDomain::FRejectTask::FRejectTask(
        TSharedPtr<FEzAcceptVersionGameSessionDomain> Self,
        Gs2::UE5::Version::Model::FEzVersionPtr Version
    ): Self(Self), Version(Version)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAcceptVersionGameSessionDomain::FRejectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Reject(
                    MakeShared<Gs2::Version::Request::FRejectRequest>()
                        ->WithVersion(Version == nullptr ? nullptr : Version->ToModel())
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
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

    TSharedPtr<FAsyncTask<FEzAcceptVersionGameSessionDomain::FRejectTask>> FEzAcceptVersionGameSessionDomain::Reject(
        Gs2::UE5::Version::Model::FEzVersionPtr Version
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FRejectTask>>(
            this->AsShared(),
            Version
        );
    }

    FEzAcceptVersionGameSessionDomain::FDeleteTask::FDeleteTask(
        TSharedPtr<FEzAcceptVersionGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAcceptVersionGameSessionDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Version::Request::FDeleteAcceptVersionRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
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

    TSharedPtr<FAsyncTask<FEzAcceptVersionGameSessionDomain::FDeleteTask>> FEzAcceptVersionGameSessionDomain::Delete(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(
            this->AsShared()
        );
    }

    FEzAcceptVersionGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzAcceptVersionGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAcceptVersionGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Version::Model::FEzAcceptVersionPtr> Result
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
                *Result = Gs2::UE5::Version::Model::FEzAcceptVersion::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzAcceptVersionGameSessionDomain::FModelTask>> FEzAcceptVersionGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzAcceptVersionGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Version::Model::FEzAcceptVersionPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Version::Model::FAcceptVersionPtr Item)
            {
                Callback(Gs2::UE5::Version::Model::FEzAcceptVersion::FromModel(Item));
            }
        );
    }

    void FEzAcceptVersionGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
