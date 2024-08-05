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

#include "Log/Domain/Model/User.h"
#include "Log/Domain/Model/Namespace.h"
#include "Log/Domain/Model/AccessLog.h"
#include "Log/Domain/Model/IssueStampSheetLog.h"
#include "Log/Domain/Model/ExecuteStampSheetLog.h"
#include "Log/Domain/Model/ExecuteStampTaskLog.h"
#include "Log/Domain/Model/InGameLog.h"
#include "Log/Domain/Model/InGameLogAccessToken.h"
#include "Log/Domain/Model/AccessLogWithTelemetry.h"
#include "Log/Domain/Model/User.h"
#include "Log/Domain/Model/UserAccessToken.h"
#include "Log/Domain/Model/Insight.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Log::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Log::Domain::FGs2LogDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FSendInGameLogTask::FSendInGameLogTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FSendInGameLogByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FSendInGameLogTask::FSendInGameLogTask(
        const FSendInGameLogTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSendInGameLogTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FInGameLogDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SendInGameLogByUserId(
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
                const auto ParentKey = Gs2::Log::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "InGameLog"
                );
                const auto Key = Gs2::Log::Domain::Model::FInGameLogDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRequestId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FInGameLog::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Log::Domain::Model::FInGameLogDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetRequestId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FSendInGameLogTask>> FUserDomain::SendInGameLog(
        Request::FSendInGameLogByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendInGameLogTask>>(this->AsShared(), Request);
    }

    Gs2::Log::Domain::Iterator::FQueryInGameLogIteratorPtr FUserDomain::InGameLog(
        const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> Tags,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FQueryInGameLogIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            Tags,
            Begin,
            End,
            LongTerm,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeInGameLog(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FInGameLog::TypeName,
            Gs2::Log::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "InGameLog"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeInGameLog(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FInGameLog::TypeName,
            Gs2::Log::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "InGameLog"
            ),
            CallbackID
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

