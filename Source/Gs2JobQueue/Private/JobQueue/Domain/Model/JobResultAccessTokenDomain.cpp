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

#include "JobQueue/Domain/Model/JobResultAccessToken.h"
#include "JobQueue/Domain/Model/JobResult.h"
#include "JobQueue/Domain/Model/Namespace.h"
#include "JobQueue/Domain/Model/Job.h"
#include "JobQueue/Domain/Model/JobAccessToken.h"
#include "JobQueue/Domain/Model/JobResult.h"
#include "JobQueue/Domain/Model/JobResultAccessToken.h"
#include "JobQueue/Domain/Model/DeadLetterJob.h"
#include "JobQueue/Domain/Model/DeadLetterJobAccessToken.h"
#include "JobQueue/Domain/Model/User.h"
#include "JobQueue/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::JobQueue::Domain::Model
{

    FJobResultAccessTokenDomain::FJobResultAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> JobName,
        const TOptional<int32> TryNumber
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        JobName(JobName),
        TryNumber(TryNumber),
        ParentKey(Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            JobName,
            "JobResult"
        ))
    {
    }

    FJobResultAccessTokenDomain::FJobResultAccessTokenDomain(
        const FJobResultAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        JobName(From.JobName),
        TryNumber(From.TryNumber),
        ParentKey(From.ParentKey)
    {

    }

    FJobResultAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FJobResultAccessTokenDomain> Self,
        const Request::FGetJobResultRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FJobResultAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJobResultAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithJobName(Self->JobName);
        const auto Future = Self->Client->GetJobResult(
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
                const auto ParentKey = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->JobName,
                    "JobResult"
                );
                const auto Key = Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetTryNumber().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetTryNumber()) : TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::JobQueue::Model::FJobResult::TypeName,
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

    TSharedPtr<FAsyncTask<FJobResultAccessTokenDomain::FGetTask>> FJobResultAccessTokenDomain::Get(
        Request::FGetJobResultRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FJobResultAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> JobName,
        TOptional<FString> TryNumber,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (JobName.IsSet() ? *JobName : "null") + ":" +
            (TryNumber.IsSet() ? *TryNumber : "null") + ":" +
            ChildType;
    }

    FString FJobResultAccessTokenDomain::CreateCacheKey(
        TOptional<FString> TryNumber
    )
    {
        return FString("") +
            (TryNumber.IsSet() ? *TryNumber : "null");
    }

    FJobResultAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FJobResultAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FJobResultAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FJobResultAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::JobQueue::Model::FJobResult> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::JobQueue::Model::FJobResult>(
            Self->ParentKey,
            Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                Self->TryNumber.IsSet() ? FString::FromInt(*Self->TryNumber) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::JobQueue::Request::FGetJobResultRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                    Self->TryNumber.IsSet() ? FString::FromInt(*Self->TryNumber) : TOptional<FString>()
                );
                Self->Cache->Put(
                    Gs2::JobQueue::Model::FJobResult::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "jobResult")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::JobQueue::Model::FJobResult>(
                Self->ParentKey,
                Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                    Self->TryNumber.IsSet() ? FString::FromInt(*Self->TryNumber) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJobResultAccessTokenDomain::FModelTask>> FJobResultAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FJobResultAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FJobResultAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::JobQueue::Model::FJobResultPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::JobQueue::Model::FJobResult::TypeName,
            ParentKey,
            Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                TryNumber.IsSet() ? FString::FromInt(*TryNumber) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::JobQueue::Model::FJobResult>(obj));
            }
        );
    }

    void FJobResultAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::JobQueue::Model::FJobResult::TypeName,
            ParentKey,
            Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                TryNumber.IsSet() ? FString::FromInt(*TryNumber) : TOptional<FString>()
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

