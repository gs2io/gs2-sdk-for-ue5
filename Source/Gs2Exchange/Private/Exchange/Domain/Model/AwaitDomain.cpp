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

    FAwaitDomain::FAwaitDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> AwaitName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        AwaitName(AwaitName),
        ParentKey(Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Await"
        ))
    {
    }

    FAwaitDomain::FAwaitDomain(
        const FAwaitDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FAwaitDomain::FGetTask::FGetTask(
        const TSharedPtr<FAwaitDomain> Self,
        const Request::FGetAwaitByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FAwait>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->GetAwaitByUserId(
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
                    Self->UserId,
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

    TSharedPtr<FAsyncTask<FAwaitDomain::FGetTask>> FAwaitDomain::Get(
        Request::FGetAwaitByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FAwaitDomain::FAcquireTask::FAcquireTask(
        const TSharedPtr<FAwaitDomain> Self,
        const Request::FAcquireByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitDomain::FAcquireTask::FAcquireTask(
        const FAcquireTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitDomain::FAcquireTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->AcquireByUserId(
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
                    Self->UserId,
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
        if (ResultModel->GetAutoRunStampSheet().IsSet() && !*ResultModel->GetAutoRunStampSheet())
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

    TSharedPtr<FAsyncTask<FAwaitDomain::FAcquireTask>> FAwaitDomain::Acquire(
        Request::FAcquireByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireTask>>(this->AsShared(), Request);
    }

    FAwaitDomain::FAcquireForceTask::FAcquireForceTask(
        const TSharedPtr<FAwaitDomain> Self,
        const Request::FAcquireForceByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitDomain::FAcquireForceTask::FAcquireForceTask(
        const FAcquireForceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitDomain::FAcquireForceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->AcquireForceByUserId(
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
                    Self->UserId,
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
        if (ResultModel->GetAutoRunStampSheet().IsSet() && !*ResultModel->GetAutoRunStampSheet())
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

    TSharedPtr<FAsyncTask<FAwaitDomain::FAcquireForceTask>> FAwaitDomain::AcquireForce(
        Request::FAcquireForceByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireForceTask>>(this->AsShared(), Request);
    }

    FAwaitDomain::FSkipTask::FSkipTask(
        const TSharedPtr<FAwaitDomain> Self,
        const Request::FSkipByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitDomain::FSkipTask::FSkipTask(
        const FSkipTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitDomain::FSkipTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->SkipByUserId(
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
                    Self->UserId,
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
        if (ResultModel->GetAutoRunStampSheet().IsSet() && !*ResultModel->GetAutoRunStampSheet())
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

    TSharedPtr<FAsyncTask<FAwaitDomain::FSkipTask>> FAwaitDomain::Skip(
        Request::FSkipByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSkipTask>>(this->AsShared(), Request);
    }

    FAwaitDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FAwaitDomain> Self,
        const Request::FDeleteAwaitByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAwaitDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithAwaitName(Self->AwaitName);
        const auto Future = Self->Client->DeleteAwaitByUserId(
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
                    Self->UserId,
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

    TSharedPtr<FAsyncTask<FAwaitDomain::FDeleteTask>> FAwaitDomain::Delete(
        Request::FDeleteAwaitByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FAwaitDomain::CreateCacheParentKey(
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

    FString FAwaitDomain::CreateCacheKey(
        TOptional<FString> AwaitName
    )
    {
        return FString() +
            (AwaitName.IsSet() ? *AwaitName : "null");
    }

    FAwaitDomain::FModelTask::FModelTask(
        const TSharedPtr<FAwaitDomain> Self
    ): Self(Self)
    {

    }

    FAwaitDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAwaitDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FAwait>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Exchange::Model::FAwait>(
            Self->ParentKey,
            Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                Self->AwaitName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Exchange::Request::FGetAwaitByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "await")
                    {
                        Self->Cache->Delete(
                            Gs2::Exchange::Model::FAwait::TypeName,
                            Self->ParentKey,
                            Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                                Self->AwaitName
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Exchange::Model::FAwait>(
                Self->ParentKey,
                Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    Self->AwaitName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAwaitDomain::FModelTask>> FAwaitDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAwaitDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

