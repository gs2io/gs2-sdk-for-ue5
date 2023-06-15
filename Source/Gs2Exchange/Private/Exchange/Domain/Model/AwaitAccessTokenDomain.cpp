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

#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/RateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/ExchangeAccessToken.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Exchange::Domain::Model
{

    FAwaitAccessTokenDomain::FAwaitAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> AwaitName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        AwaitName(AwaitName),
        ParentKey(Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Await"
        ))
    {
    }

    FAwaitAccessTokenDomain::FAwaitAccessTokenDomain(
        const FAwaitAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FAwaitAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FAwaitAccessTokenDomain> Self,
        const Request::FGetAwaitRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FAwait>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->GetAwait(
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
                const auto ParentKey = Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Await"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Exchange::Model::FAwait::TypeName,
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

    TSharedPtr<FAsyncTask<FAwaitAccessTokenDomain::FGetTask>> FAwaitAccessTokenDomain::Get(
        Request::FGetAwaitRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FAwaitAccessTokenDomain::FAcquireTask::FAcquireTask(
        const TSharedPtr<FAwaitAccessTokenDomain> Self,
        const Request::FAcquireRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitAccessTokenDomain::FAcquireTask::FAcquireTask(
        const FAcquireTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitAccessTokenDomain::FAcquireTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->Acquire(
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
                const auto ParentKey = Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Await"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Exchange::Model::FAwait::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto StampSheet = MakeShared<Gs2::Core::Domain::Model::FStampSheetDomain>(
                Self->Cache,
                Self->JobQueueDomain,
                Self->Session,
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId(),
                Self->StampSheetConfiguration
            );
            const auto Future3 = StampSheet->Run();
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return MakeShared<Core::Model::FTransactionError<Gs2::Core::Domain::Model::FStampSheetDomain::FRunTask>>(
                    Future3->GetTask().Error()->GetErrors(),
                    [&]() -> TSharedPtr<FAsyncTask<Gs2::Core::Domain::Model::FStampSheetDomain::FRunTask>>
                    {
                        return MakeShared<Gs2::Core::Domain::Model::FStampSheetDomain>(
                            Self->Cache,
                            Self->JobQueueDomain,
                            Self->Session,
                            *ResultModel->GetStampSheet(),
                            *ResultModel->GetStampSheetEncryptionKeyId(),
                            Self->StampSheetConfiguration
                        )->Run();
                    }
                );
            }
            Future3->EnsureCompletion();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAwaitAccessTokenDomain::FAcquireTask>> FAwaitAccessTokenDomain::Acquire(
        Request::FAcquireRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireTask>>(this->AsShared(), Request);
    }

    FAwaitAccessTokenDomain::FSkipTask::FSkipTask(
        const TSharedPtr<FAwaitAccessTokenDomain> Self,
        const Request::FSkipRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitAccessTokenDomain::FSkipTask::FSkipTask(
        const FSkipTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitAccessTokenDomain::FSkipTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->Skip(
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
                const auto ParentKey = Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Await"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Exchange::Model::FAwait::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto StampSheet = MakeShared<Gs2::Core::Domain::Model::FStampSheetDomain>(
                Self->Cache,
                Self->JobQueueDomain,
                Self->Session,
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId(),
                Self->StampSheetConfiguration
            );
            const auto Future3 = StampSheet->Run();
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return MakeShared<Core::Model::FTransactionError<Gs2::Core::Domain::Model::FStampSheetDomain::FRunTask>>(
                    Future3->GetTask().Error()->GetErrors(),
                    [&]() -> TSharedPtr<FAsyncTask<Gs2::Core::Domain::Model::FStampSheetDomain::FRunTask>>
                    {
                        return MakeShared<Gs2::Core::Domain::Model::FStampSheetDomain>(
                            Self->Cache,
                            Self->JobQueueDomain,
                            Self->Session,
                            *ResultModel->GetStampSheet(),
                            *ResultModel->GetStampSheetEncryptionKeyId(),
                            Self->StampSheetConfiguration
                        )->Run();
                    }
                );
            }
            Future3->EnsureCompletion();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAwaitAccessTokenDomain::FSkipTask>> FAwaitAccessTokenDomain::Skip(
        Request::FSkipRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSkipTask>>(this->AsShared(), Request);
    }

    FAwaitAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FAwaitAccessTokenDomain> Self,
        const Request::FDeleteAwaitRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->DeleteAwait(
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
                const auto ParentKey = Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Await"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Exchange::Model::FAwait::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAwaitAccessTokenDomain::FDeleteTask>> FAwaitAccessTokenDomain::Delete(
        Request::FDeleteAwaitRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FAwaitAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> AwaitName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (AwaitName.IsSet() ? *AwaitName : "null") + ":" +
            ChildType;
    }

    FString FAwaitAccessTokenDomain::CreateCacheKey(
        TOptional<FString> AwaitName
    )
    {
        return FString() +
            (AwaitName.IsSet() ? *AwaitName : "null");
    }

    FAwaitAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FAwaitAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FAwaitAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FAwait>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Exchange::Model::FAwait> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Exchange::Model::FAwait>(
            Self->ParentKey,
            Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                Self->AwaitName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Exchange::Request::FGetAwaitRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    Self->AwaitName
                );
                Self->Cache->Put(
                    Gs2::Exchange::Model::FAwait::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "await")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Exchange::Model::FAwait>(
                Self->ParentKey,
                Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    Self->AwaitName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAwaitAccessTokenDomain::FModelTask>> FAwaitAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAwaitAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

