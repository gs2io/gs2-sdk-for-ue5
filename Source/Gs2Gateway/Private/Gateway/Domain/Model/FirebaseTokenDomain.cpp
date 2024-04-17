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

#include "Gateway/Domain/Model/FirebaseToken.h"
#include "Gateway/Domain/Model/Namespace.h"
#include "Gateway/Domain/Model/WebSocketSession.h"
#include "Gateway/Domain/Model/WebSocketSessionAccessToken.h"
#include "Gateway/Domain/Model/FirebaseToken.h"
#include "Gateway/Domain/Model/FirebaseTokenAccessToken.h"
#include "Gateway/Domain/Model/User.h"
#include "Gateway/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Gateway::Domain::Model
{

    FFirebaseTokenDomain::FFirebaseTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Gateway::Domain::FGs2GatewayDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Gateway::FGs2GatewayRestClient>(Gs2->RestSession)),
        Wsclient(MakeShared<Gs2::Gateway::FGs2GatewayWebSocketClient>(Gs2->WebSocketSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "FirebaseToken"
        ))
    {
    }

    FFirebaseTokenDomain::FFirebaseTokenDomain(
        const FFirebaseTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        Wsclient(From.Wsclient),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FFirebaseTokenDomain::FSetTask::FSetTask(
        const TSharedPtr<FFirebaseTokenDomain>& Self,
        const Request::FSetFirebaseTokenByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFirebaseTokenDomain::FSetTask::FSetTask(
        const FSetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFirebaseTokenDomain::FSetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SetFirebaseTokenByUserId(
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
                const auto ParentKey = Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "FirebaseToken"
                );
                const auto Key = Gs2::Gateway::Domain::Model::FFirebaseTokenDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Gateway::Model::FFirebaseToken::TypeName,
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

    TSharedPtr<FAsyncTask<FFirebaseTokenDomain::FSetTask>> FFirebaseTokenDomain::Set(
        Request::FSetFirebaseTokenByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetTask>>(this->AsShared(), Request);
    }

    FFirebaseTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FFirebaseTokenDomain>& Self,
        const Request::FGetFirebaseTokenByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFirebaseTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFirebaseTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Model::FFirebaseToken>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetFirebaseTokenByUserId(
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
                const auto ParentKey = Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "FirebaseToken"
                );
                const auto Key = Gs2::Gateway::Domain::Model::FFirebaseTokenDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Gateway::Model::FFirebaseToken::TypeName,
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

    TSharedPtr<FAsyncTask<FFirebaseTokenDomain::FGetTask>> FFirebaseTokenDomain::Get(
        Request::FGetFirebaseTokenByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FFirebaseTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FFirebaseTokenDomain>& Self,
        const Request::FDeleteFirebaseTokenByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFirebaseTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFirebaseTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteFirebaseTokenByUserId(
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
                const auto ParentKey = Gs2::Gateway::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "FirebaseToken"
                );
                const auto Key = Gs2::Gateway::Domain::Model::FFirebaseTokenDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Delete(Gs2::Gateway::Model::FFirebaseToken::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFirebaseTokenDomain::FDeleteTask>> FFirebaseTokenDomain::Delete(
        Request::FDeleteFirebaseTokenByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FFirebaseTokenDomain::FSendMobileNotificationTask::FSendMobileNotificationTask(
        const TSharedPtr<FFirebaseTokenDomain>& Self,
        const Request::FSendMobileNotificationByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFirebaseTokenDomain::FSendMobileNotificationTask::FSendMobileNotificationTask(
        const FSendMobileNotificationTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFirebaseTokenDomain::FSendMobileNotificationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SendMobileNotificationByUserId(
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
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFirebaseTokenDomain::FSendMobileNotificationTask>> FFirebaseTokenDomain::SendMobileNotification(
        Request::FSendMobileNotificationByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendMobileNotificationTask>>(this->AsShared(), Request);
    }

    FString FFirebaseTokenDomain::CreateCacheParentKey(
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

    FString FFirebaseTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FFirebaseTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FFirebaseTokenDomain> Self
    ): Self(Self)
    {

    }

    FFirebaseTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFirebaseTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Gateway::Model::FFirebaseToken>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Gateway::Model::FFirebaseToken> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Gateway::Model::FFirebaseToken>(
            Self->ParentKey,
            Gs2::Gateway::Domain::Model::FFirebaseTokenDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Gateway::Request::FGetFirebaseTokenByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Gateway::Domain::Model::FFirebaseTokenDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Gateway::Model::FFirebaseToken::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "firebaseToken")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Gateway::Model::FFirebaseToken>(
                Self->ParentKey,
                Gs2::Gateway::Domain::Model::FFirebaseTokenDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFirebaseTokenDomain::FModelTask>> FFirebaseTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFirebaseTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FFirebaseTokenDomain::Subscribe(
        TFunction<void(Gs2::Gateway::Model::FFirebaseTokenPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Gateway::Model::FFirebaseToken::TypeName,
            ParentKey,
            Gs2::Gateway::Domain::Model::FFirebaseTokenDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Gateway::Model::FFirebaseToken>(obj));
            }
        );
    }

    void FFirebaseTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Gateway::Model::FFirebaseToken::TypeName,
            ParentKey,
            Gs2::Gateway::Domain::Model::FFirebaseTokenDomain::CreateCacheKey(
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

