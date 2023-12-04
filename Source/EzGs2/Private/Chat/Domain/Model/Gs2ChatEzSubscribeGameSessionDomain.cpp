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

#include "Chat/Domain/Model/Gs2ChatEzSubscribeGameSessionDomain.h"

namespace Gs2::UE5::Chat::Domain::Model
{

    TOptional<FString> FEzSubscribeGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSubscribeGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzSubscribeGameSessionDomain::RoomName() const
    {
        return Domain->RoomName;
    }

    FEzSubscribeGameSessionDomain::FEzSubscribeGameSessionDomain(
        Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzSubscribeGameSessionDomain::FSubscribeTask::FSubscribeTask(
        TSharedPtr<FEzSubscribeGameSessionDomain> Self,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes
    ): Self(Self), NotificationTypes(NotificationTypes)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscribeGameSessionDomain::FSubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Subscribe(
                    MakeShared<Gs2::Chat::Request::FSubscribeRequest>()
                        ->WithNotificationTypes([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Chat::Model::FNotificationType>>>();
                            if (!NotificationTypes.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *NotificationTypes) {
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
                *Result = MakeShared<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzSubscribeGameSessionDomain::FSubscribeTask>> FEzSubscribeGameSessionDomain::Subscribe(
        TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTask>>(
            this->AsShared(),
            NotificationTypes
        );
    }

    FEzSubscribeGameSessionDomain::FUpdateSubscribeSettingTask::FUpdateSubscribeSettingTask(
        TSharedPtr<FEzSubscribeGameSessionDomain> Self,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes
    ): Self(Self), NotificationTypes(NotificationTypes)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscribeGameSessionDomain::FUpdateSubscribeSettingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->UpdateNotificationType(
                    MakeShared<Gs2::Chat::Request::FUpdateNotificationTypeRequest>()
                        ->WithNotificationTypes([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Chat::Model::FNotificationType>>>();
                            if (!NotificationTypes.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *NotificationTypes) {
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
                *Result = MakeShared<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzSubscribeGameSessionDomain::FUpdateSubscribeSettingTask>> FEzSubscribeGameSessionDomain::UpdateSubscribeSetting(
        TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateSubscribeSettingTask>>(
            this->AsShared(),
            NotificationTypes
        );
    }

    FEzSubscribeGameSessionDomain::FUnsubscribeTask::FUnsubscribeTask(
        TSharedPtr<FEzSubscribeGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscribeGameSessionDomain::FUnsubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Unsubscribe(
                    MakeShared<Gs2::Chat::Request::FUnsubscribeRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzSubscribeGameSessionDomain::FUnsubscribeTask>> FEzSubscribeGameSessionDomain::Unsubscribe(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUnsubscribeTask>>(
            this->AsShared()
        );
    }

    FEzSubscribeGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSubscribeGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscribeGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Chat::Model::FEzSubscribePtr> Result
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
                *Result = Gs2::UE5::Chat::Model::FEzSubscribe::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSubscribeGameSessionDomain::FModelTask>> FEzSubscribeGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSubscribeGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Chat::Model::FEzSubscribePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Chat::Model::FSubscribePtr Item)
            {
                Callback(Gs2::UE5::Chat::Model::FEzSubscribe::FromModel(Item));
            }
        );
    }

    void FEzSubscribeGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
