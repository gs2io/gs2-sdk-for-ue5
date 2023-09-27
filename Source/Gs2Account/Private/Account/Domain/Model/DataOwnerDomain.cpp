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

#include "Account/Domain/Model/DataOwner.h"
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

    FDataOwnerDomain::FDataOwnerDomain(
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
        ParentKey(Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "DataOwner"
        ))
    {
    }

    FDataOwnerDomain::FDataOwnerDomain(
        const FDataOwnerDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FDataOwnerDomain::FGetTask::FGetTask(
        const TSharedPtr<FDataOwnerDomain> Self,
        const Request::FGetDataOwnerByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataOwnerDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataOwnerDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FDataOwner>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetDataOwnerByUserId(
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
                Self->Cache->Put(
                    Gs2::Account::Model::FDataOwner::TypeName,
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

    TSharedPtr<FAsyncTask<FDataOwnerDomain::FGetTask>> FDataOwnerDomain::Get(
        Request::FGetDataOwnerByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FDataOwnerDomain::CreateCacheParentKey(
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

    FString FDataOwnerDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FDataOwnerDomain::FModelTask::FModelTask(
        const TSharedPtr<FDataOwnerDomain> Self
    ): Self(Self)
    {

    }

    FDataOwnerDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDataOwnerDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FDataOwner>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Account::Model::FDataOwner> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Account::Model::FDataOwner>(
            Self->ParentKey,
            Gs2::Account::Domain::Model::FDataOwnerDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Account::Request::FGetDataOwnerByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Account::Domain::Model::FDataOwnerDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::Account::Model::FDataOwner::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "dataOwner")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Account::Model::FDataOwner>(
                Self->ParentKey,
                Gs2::Account::Domain::Model::FDataOwnerDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataOwnerDomain::FModelTask>> FDataOwnerDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDataOwnerDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FDataOwnerDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FDataOwnerPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Account::Model::FDataOwner::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FDataOwnerDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FDataOwner>(obj));
            }
        );
    }

    void FDataOwnerDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Account::Model::FDataOwner::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FDataOwnerDomain::CreateCacheKey(
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

