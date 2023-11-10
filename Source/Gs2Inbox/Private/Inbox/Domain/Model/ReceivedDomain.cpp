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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Inbox/Domain/Model/Received.h"
#include "Inbox/Domain/Model/Namespace.h"
#include "Inbox/Domain/Model/User.h"
#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Domain/Model/Message.h"
#include "Inbox/Domain/Model/MessageAccessToken.h"
#include "Inbox/Domain/Model/CurrentMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessage.h"
#include "Inbox/Domain/Model/Received.h"
#include "Inbox/Domain/Model/ReceivedAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FReceivedDomain::FReceivedDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inbox::Domain::FGs2InboxDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Received"
        ))
    {
    }

    FReceivedDomain::FReceivedDomain(
        const FReceivedDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FReceivedDomain::FGetTask::FGetTask(
        const TSharedPtr<FReceivedDomain>& Self,
        const Request::FGetReceivedByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceivedDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceivedDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FReceived>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetReceivedByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Received"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inbox::Model::FReceived::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceivedDomain::FGetTask>> FReceivedDomain::Get(
        Request::FGetReceivedByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FReceivedDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FReceivedDomain>& Self,
        const Request::FUpdateReceivedByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceivedDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceivedDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FReceivedDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->UpdateReceivedByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Received"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inbox::Model::FReceived::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceivedDomain::FUpdateTask>> FReceivedDomain::Update(
        Request::FUpdateReceivedByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FReceivedDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FReceivedDomain>& Self,
        const Request::FDeleteReceivedByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceivedDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceivedDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FReceivedDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteReceivedByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Received"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Delete(Gs2::Inbox::Model::FReceived::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceivedDomain::FDeleteTask>> FReceivedDomain::Delete(
        Request::FDeleteReceivedByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FReceivedDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FReceivedDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FReceivedDomain::FModelTask::FModelTask(
        const TSharedPtr<FReceivedDomain> Self
    ): Self(Self)
    {

    }

    FReceivedDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceivedDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FReceived>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inbox::Model::FReceived> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inbox::Model::FReceived>(
            Self->ParentKey,
            Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inbox::Request::FGetReceivedByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inbox::Model::FReceived::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "received")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Inbox::Model::FReceived>(
                Self->ParentKey,
                Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceivedDomain::FModelTask>> FReceivedDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceivedDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FReceivedDomain::Subscribe(
        TFunction<void(Gs2::Inbox::Model::FReceivedPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inbox::Model::FReceived::TypeName,
            ParentKey,
            Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inbox::Model::FReceived>(obj));
            }
        );
    }

    void FReceivedDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inbox::Model::FReceived::TypeName,
            ParentKey,
            Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

