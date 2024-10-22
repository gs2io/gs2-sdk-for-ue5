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

#include "Log/Domain/Model/InGameLog.h"
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

    FInGameLogDomain::FInGameLogDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Log::Domain::FGs2LogDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> RequestId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        RequestId(RequestId),
        ParentKey(Gs2::Log::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "InGameLog"
        ))
    {
    }

    FInGameLogDomain::FInGameLogDomain(
        const FInGameLogDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        RequestId(From.RequestId),
        ParentKey(From.ParentKey)
    {

    }

    FString FInGameLogDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RequestId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RequestId.IsSet() ? *RequestId : "null") + ":" +
            ChildType;
    }

    FString FInGameLogDomain::CreateCacheKey(
        TOptional<FString> RequestId
    )
    {
        return FString("") +
            (RequestId.IsSet() ? *RequestId : "null");
    }

    FInGameLogDomain::FModelTask::FModelTask(
        const TSharedPtr<FInGameLogDomain> Self
    ): Self(Self)
    {

    }

    FInGameLogDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FInGameLogDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FInGameLog>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Log::Model::FInGameLog> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Log::Model::FInGameLog>(
            Self->ParentKey,
            Gs2::Log::Domain::Model::FInGameLogDomain::CreateCacheKey(
                Self->RequestId
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInGameLogDomain::FModelTask>> FInGameLogDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FInGameLogDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FInGameLogDomain::Subscribe(
        TFunction<void(Gs2::Log::Model::FInGameLogPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Log::Model::FInGameLog::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FInGameLogDomain::CreateCacheKey(
                RequestId
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Log::Model::FInGameLog>(obj));
            }
        );
    }

    void FInGameLogDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Log::Model::FInGameLog::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FInGameLogDomain::CreateCacheKey(
                RequestId
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

