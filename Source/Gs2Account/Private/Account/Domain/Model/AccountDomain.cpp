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

#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Account::Domain::Model
{

    FAccountDomain::FAccountDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Account"
        ))
    {
    }

    FAccountDomain::FAccountDomain(
        const FAccountDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FAccountDomain::FUpdateTimeOffsetTask::FUpdateTimeOffsetTask(
        const TSharedPtr<FAccountDomain>& Self,
        const Request::FUpdateTimeOffsetRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccountDomain::FUpdateTimeOffsetTask::FUpdateTimeOffsetTask(
        const FUpdateTimeOffsetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountDomain::FUpdateTimeOffsetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->UpdateTimeOffset(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Account"
                );
                const auto Key = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                    Self->UserId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FAccount::TypeName,
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

    TSharedPtr<FAsyncTask<FAccountDomain::FUpdateTimeOffsetTask>> FAccountDomain::UpdateTimeOffset(
        Request::FUpdateTimeOffsetRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTimeOffsetTask>>(this->AsShared(), Request);
    }

    FAccountDomain::FUpdateBannedTask::FUpdateBannedTask(
        const TSharedPtr<FAccountDomain>& Self,
        const Request::FUpdateBannedRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccountDomain::FUpdateBannedTask::FUpdateBannedTask(
        const FUpdateBannedTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountDomain::FUpdateBannedTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->UpdateBanned(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Account"
                );
                const auto Key = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FAccount::TypeName,
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

    TSharedPtr<FAsyncTask<FAccountDomain::FUpdateBannedTask>> FAccountDomain::UpdateBanned(
        Request::FUpdateBannedRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateBannedTask>>(this->AsShared(), Request);
    }

    FAccountDomain::FAddBanTask::FAddBanTask(
        const TSharedPtr<FAccountDomain>& Self,
        const Request::FAddBanRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccountDomain::FAddBanTask::FAddBanTask(
        const FAddBanTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountDomain::FAddBanTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->AddBan(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Account"
                );
                const auto Key = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FAccount::TypeName,
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

    TSharedPtr<FAsyncTask<FAccountDomain::FAddBanTask>> FAccountDomain::AddBan(
        Request::FAddBanRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddBanTask>>(this->AsShared(), Request);
    }

    FAccountDomain::FRemoveBanTask::FRemoveBanTask(
        const TSharedPtr<FAccountDomain>& Self,
        const Request::FRemoveBanRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccountDomain::FRemoveBanTask::FRemoveBanTask(
        const FRemoveBanTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountDomain::FRemoveBanTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->RemoveBan(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Account"
                );
                const auto Key = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FAccount::TypeName,
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

    TSharedPtr<FAsyncTask<FAccountDomain::FRemoveBanTask>> FAccountDomain::RemoveBan(
        Request::FRemoveBanRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRemoveBanTask>>(this->AsShared(), Request);
    }

    FAccountDomain::FGetTask::FGetTask(
        const TSharedPtr<FAccountDomain>& Self,
        const Request::FGetAccountRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccountDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FAccount>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetAccount(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Account"
                );
                const auto Key = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                    Self->UserId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FAccount::TypeName,
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

    TSharedPtr<FAsyncTask<FAccountDomain::FGetTask>> FAccountDomain::Get(
        Request::FGetAccountRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FAccountDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FAccountDomain>& Self,
        const Request::FDeleteAccountRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccountDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteAccount(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Account"
                );
                const auto Key = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                    Self->UserId
                );
                Self->Gs2->Cache->Delete(Gs2::Account::Model::FAccount::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccountDomain::FDeleteTask>> FAccountDomain::Delete(
        Request::FDeleteAccountRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FAccountDomain::FAuthenticationTask::FAuthenticationTask(
        const TSharedPtr<FAccountDomain>& Self,
        const Request::FAuthenticationRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccountDomain::FAuthenticationTask::FAuthenticationTask(
        const FAuthenticationTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountDomain::FAuthenticationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->Authentication(
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
                const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Account"
                );
                const auto Key = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                    Self->UserId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FAccount::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetBody().IsSet())
            {
                Domain->Body = *ResultModel->GetBody();
            }
            if (ResultModel->GetSignature().IsSet())
            {
                Domain->Signature = *ResultModel->GetSignature();
            }
            if (ResultModel->GetBanStatuses() != nullptr)
            {
                Domain->BanStatuses = ResultModel->GetBanStatuses();
            }
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccountDomain::FAuthenticationTask>> FAccountDomain::Authentication(
        Request::FAuthenticationRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAuthenticationTask>>(this->AsShared(), Request);
    }

    FAccountDomain::FDeleteDataOwnerTask::FDeleteDataOwnerTask(
        const TSharedPtr<FAccountDomain>& Self,
        const Request::FDeleteDataOwnerByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccountDomain::FDeleteDataOwnerTask::FDeleteDataOwnerTask(
        const FDeleteDataOwnerTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountDomain::FDeleteDataOwnerTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FDataOwnerDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteDataOwnerByUserId(
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
                    "DataOwner"
                );
                const auto Key = Gs2::Account::Domain::Model::FDataOwnerDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Delete(Gs2::Account::Model::FDataOwner::TypeName, ParentKey, Key);
            }
        }
        auto Domain = MakeShared<Gs2::Account::Domain::Model::FDataOwnerDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccountDomain::FDeleteDataOwnerTask>> FAccountDomain::DeleteDataOwner(
        Request::FDeleteDataOwnerByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteDataOwnerTask>>(this->AsShared(), Request);
    }

    Gs2::Account::Domain::Iterator::FDescribeTakeOversByUserIdIteratorPtr FAccountDomain::TakeOvers(
    ) const
    {
        return MakeShared<Gs2::Account::Domain::Iterator::FDescribeTakeOversByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FAccountDomain::SubscribeTakeOvers(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "TakeOver"
            ),
            Callback
        );
    }

    void FAccountDomain::UnsubscribeTakeOvers(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "TakeOver"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain> FAccountDomain::TakeOver(
        const int32 Type
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FTakeOverDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            Type
        );
    }

    TSharedPtr<Gs2::Account::Domain::Model::FDataOwnerDomain> FAccountDomain::DataOwner(
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FDataOwnerDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    FString FAccountDomain::CreateCacheParentKey(
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

    FString FAccountDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }

    FAccountDomain::FModelTask::FModelTask(
        const TSharedPtr<FAccountDomain> Self
    ): Self(Self)
    {

    }

    FAccountDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FAccount>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Account::Model::FAccount> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Account::Model::FAccount>(
            Self->ParentKey,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                Self->UserId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Account::Request::FGetAccountRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                    Self->UserId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FAccount::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "account")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Account::Model::FAccount>(
                Self->ParentKey,
                Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                    Self->UserId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccountDomain::FModelTask>> FAccountDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAccountDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FAccountDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FAccountPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FAccount::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                UserId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FAccount>(obj));
            }
        );
    }

    void FAccountDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FAccount::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                UserId
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

