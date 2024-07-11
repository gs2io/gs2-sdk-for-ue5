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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Account/Domain/Model/PlatformId.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/PlatformId.h"
#include "Account/Domain/Model/PlatformIdAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Account::Domain::Model
{

    FPlatformIdDomain::FPlatformIdDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<int32> Type,
        const TOptional<FString> UserIdentifier
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        Type(Type),
        UserIdentifier(UserIdentifier),
        ParentKey(Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "PlatformId"
        ))
    {
    }

    FPlatformIdDomain::FPlatformIdDomain(
        const FPlatformIdDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        Type(From.Type),
        UserIdentifier(From.UserIdentifier),
        ParentKey(From.ParentKey)
    {

    }

    FPlatformIdDomain::FGetTask::FGetTask(
        const TSharedPtr<FPlatformIdDomain>& Self,
        const Request::FGetPlatformIdByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPlatformIdDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPlatformIdDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FPlatformId>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithType(Self->Type);
        const auto Future = Self->Client->GetPlatformIdByUserId(
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
            *Result = ResultModel->GetItem();
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPlatformIdDomain::FGetTask>> FPlatformIdDomain::Get(
        Request::FGetPlatformIdByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPlatformIdDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FPlatformIdDomain>& Self,
        const Request::FCreatePlatformIdByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPlatformIdDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPlatformIdDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithType(Self->Type)
            ->WithUserIdentifier(Self->UserIdentifier);
        const auto Future = Self->Client->CreatePlatformIdByUserId(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "PlatformId"
                );
                const auto Key = Gs2::Account::Domain::Model::FPlatformIdDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>(),
                    ResultModel->GetItem()->GetUserIdentifier()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FPlatformId::TypeName,
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

    TSharedPtr<FAsyncTask<FPlatformIdDomain::FCreateTask>> FPlatformIdDomain::Create(
        Request::FCreatePlatformIdByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FPlatformIdDomain::FFindTask::FFindTask(
        const TSharedPtr<FPlatformIdDomain>& Self,
        const Request::FFindPlatformIdByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPlatformIdDomain::FFindTask::FFindTask(
        const FFindTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPlatformIdDomain::FFindTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FPlatformUser>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithType(Self->Type)
            ->WithUserIdentifier(Self->UserIdentifier);
        const auto Future = Self->Client->FindPlatformIdByUserId(
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
            *Result = ResultModel->GetItem();
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPlatformIdDomain::FFindTask>> FPlatformIdDomain::Find(
        Request::FFindPlatformIdByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FFindTask>>(this->AsShared(), Request);
    }

    FString FPlatformIdDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> Type,
        TOptional<FString> UserIdentifier,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (Type.IsSet() ? *Type : "null") + ":" +
            (UserIdentifier.IsSet() ? *UserIdentifier : "null") + ":" +
            ChildType;
    }

    FString FPlatformIdDomain::CreateCacheKey(
        TOptional<FString> Type,
        TOptional<FString> UserIdentifier
    )
    {
        return FString("") +
            (Type.IsSet() ? *Type : "null") + ":" + 
            (UserIdentifier.IsSet() ? *UserIdentifier : "null");
    }

    FPlatformIdDomain::FModelTask::FModelTask(
        const TSharedPtr<FPlatformIdDomain> Self
    ): Self(Self)
    {

    }

    FPlatformIdDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPlatformIdDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FPlatformId>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Account::Model::FPlatformId> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Account::Model::FPlatformId>(
            Self->ParentKey,
            Gs2::Account::Domain::Model::FPlatformIdDomain::CreateCacheKey(
                Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>(),
                Self->UserIdentifier
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Account::Request::FGetPlatformIdByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Account::Domain::Model::FPlatformIdDomain::CreateCacheKey(
                    Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>(),
                    Self->UserIdentifier
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FPlatformId::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "platformId")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Account::Model::FPlatformId>(
                Self->ParentKey,
                Gs2::Account::Domain::Model::FPlatformIdDomain::CreateCacheKey(
                    Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>(),
                    Self->UserIdentifier
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPlatformIdDomain::FModelTask>> FPlatformIdDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPlatformIdDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FPlatformIdDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FPlatformIdPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FPlatformId::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FPlatformIdDomain::CreateCacheKey(
                Type.IsSet() ? FString::FromInt(*Type) : TOptional<FString>(),
                UserIdentifier
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FPlatformId>(obj));
            }
        );
    }

    void FPlatformIdDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FPlatformId::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FPlatformIdDomain::CreateCacheKey(
                Type.IsSet() ? FString::FromInt(*Type) : TOptional<FString>(),
                UserIdentifier
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

