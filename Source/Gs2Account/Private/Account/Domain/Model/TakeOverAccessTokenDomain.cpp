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

#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Account::Domain::Model
{

    FTakeOverAccessTokenDomain::FTakeOverAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<int32> Type
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        Type(Type),
        ParentKey(Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "TakeOver"
        ))
    {
    }

    FTakeOverAccessTokenDomain::FTakeOverAccessTokenDomain(
        const FTakeOverAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        Type(From.Type),
        ParentKey(From.ParentKey)
    {

    }

    FTakeOverAccessTokenDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FTakeOverAccessTokenDomain> Self,
        const Request::FCreateTakeOverRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverAccessTokenDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto Future = Self->Client->CreateTakeOver(
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
                    Self->UserId(),
                    "TakeOver"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Account::Model::FTakeOver::TypeName,
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

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FCreateTask>> FTakeOverAccessTokenDomain::Create(
        Request::FCreateTakeOverRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FTakeOverAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FTakeOverAccessTokenDomain> Self,
        const Request::FGetTakeOverRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOver>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto Future = Self->Client->GetTakeOver(
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
                    Self->UserId(),
                    "TakeOver"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Account::Model::FTakeOver::TypeName,
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

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FGetTask>> FTakeOverAccessTokenDomain::Get(
        Request::FGetTakeOverRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FTakeOverAccessTokenDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FTakeOverAccessTokenDomain> Self,
        const Request::FUpdateTakeOverRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverAccessTokenDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto Future = Self->Client->UpdateTakeOver(
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
                    Self->UserId(),
                    "TakeOver"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Account::Model::FTakeOver::TypeName,
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

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FUpdateTask>> FTakeOverAccessTokenDomain::Update(
        Request::FUpdateTakeOverRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FTakeOverAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FTakeOverAccessTokenDomain> Self,
        const Request::FDeleteTakeOverRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto Future = Self->Client->DeleteTakeOver(
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
                    Self->UserId(),
                    "TakeOver"
                );
                const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetType().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetType()) : TOptional<FString>()
                );
                Self->Cache->Delete(Gs2::Account::Model::FTakeOver::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FDeleteTask>> FTakeOverAccessTokenDomain::Delete(
        Request::FDeleteTakeOverRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FTakeOverAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> Type,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (Type.IsSet() ? *Type : "null") + ":" +
            ChildType;
    }

    FString FTakeOverAccessTokenDomain::CreateCacheKey(
        TOptional<FString> Type
    )
    {
        return FString("") +
            (Type.IsSet() ? *Type : "null");
    }

    FTakeOverAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FTakeOverAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FTakeOverAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOver>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Account::Model::FTakeOver> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Account::Model::FTakeOver>(
            Self->ParentKey,
            Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Account::Request::FGetTakeOverRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::Account::Model::FTakeOver::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "takeOver")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Account::Model::FTakeOver>(
                Self->ParentKey,
                Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                    Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FModelTask>> FTakeOverAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTakeOverAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

