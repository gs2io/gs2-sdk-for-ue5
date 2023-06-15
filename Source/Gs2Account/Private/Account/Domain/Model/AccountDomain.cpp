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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Account::Domain::Model
{

    FAccountDomain::FAccountDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Account"
        ))
    {

    }

    FAccountDomain::FUpdateTimeOffsetTask::FUpdateTimeOffsetTask(
        const TSharedPtr<FAccountDomain> Self,
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
                Self->Cache->Put(
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
        const TSharedPtr<FAccountDomain> Self,
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
                    Self->UserId
                );
                Self->Cache->Put(
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

    FAccountDomain::FGetTask::FGetTask(
        const TSharedPtr<FAccountDomain> Self,
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
                Self->Cache->Put(
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
        const TSharedPtr<FAccountDomain> Self,
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
                Self->Cache->Delete(Gs2::Account::Model::FAccount::TypeName, ParentKey, Key);
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
        const TSharedPtr<FAccountDomain> Self,
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
                Self->Cache->Put(
                    Gs2::Account::Model::FAccount::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        Domain->Body = *ResultModel->GetBody();
        Domain->Signature = *ResultModel->GetSignature();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccountDomain::FAuthenticationTask>> FAccountDomain::Authentication(
        Request::FAuthenticationRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAuthenticationTask>>(this->AsShared(), Request);
    }

    FAccountDomain::FDeleteDataOwnerTask::FDeleteDataOwnerTask(
        const TSharedPtr<FAccountDomain> Self,
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
                Self->Cache->Delete(Gs2::Account::Model::FDataOwner::TypeName, ParentKey, Key);
            }
        }
        auto Domain = MakeShared<Gs2::Account::Domain::Model::FDataOwnerDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
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
            Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain> FAccountDomain::TakeOver(
        const int32 Type
    ) const
    {
        return MakeShared<Gs2::Account::Domain::Model::FTakeOverDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            Type
        );
    }

    TSharedPtr<Gs2::Account::Domain::Model::FDataOwnerDomain> FAccountDomain::DataOwner(
    ) const
    {
        return MakeShared<Gs2::Account::Domain::Model::FDataOwnerDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
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
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FAccountDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString() +
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
        Gs2::Account::Model::FAccountPtr Value;
        const auto bCacheHit = Self->Cache->TryGet<Gs2::Account::Model::FAccount>(
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

                Self->Cache->Put(
                    Gs2::Account::Model::FAccount::TypeName,
                    Self->ParentKey,
                    Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                        Self->UserId
                    ),
                    nullptr,
                 FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "account")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Account::Model::FAccount>(
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
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

