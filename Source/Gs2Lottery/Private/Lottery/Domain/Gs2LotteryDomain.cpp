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

// ReSharper disable CppUnusedIncludeDirective

#include "Lottery/Domain/Gs2Lottery.h"
#include "Lottery/Domain/Model/Namespace.h"
#include "Lottery/Domain/Model/LotteryModelMaster.h"
#include "Lottery/Domain/Model/PrizeTableMaster.h"
#include "Lottery/Domain/Model/LotteryModel.h"
#include "Lottery/Domain/Model/PrizeTable.h"
#include "Lottery/Domain/Model/Lottery.h"
#include "Lottery/Domain/Model/Probability.h"
#include "Lottery/Domain/Model/CurrentLotteryMaster.h"
#include "Lottery/Domain/Model/PrizeLimit.h"
#include "Lottery/Domain/Model/BoxItems.h"
#include "Lottery/Domain/Model/User.h"
#include "Lottery/Domain/Model/UserAccessToken.h"

namespace Gs2::Lottery::Domain
{

    FGs2LotteryDomain::FGs2LotteryDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Session)),
        ParentKey("lottery")
    {
    }

    FGs2LotteryDomain::FGs2LotteryDomain(
        const FGs2LotteryDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2LotteryDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2LotteryDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2LotteryDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2LotteryDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateNamespace(
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
            
            {
                const auto ParentKey = FString("lottery:Namespace");
                const auto Key = Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Lottery::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Lottery::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2LotteryDomain::FCreateNamespaceTask>> FGs2LotteryDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2LotteryDomain::FDumpUserDataTask::FDumpUserDataTask(
        TSharedPtr<FGs2LotteryDomain> Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2LotteryDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2LotteryDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2LotteryDomain>> Result
    )
    {
        const auto Future = Self->Client->DumpUserDataByUserId(
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
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2LotteryDomain::FDumpUserDataTask>> FGs2LotteryDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2LotteryDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        TSharedPtr<FGs2LotteryDomain> Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2LotteryDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2LotteryDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2LotteryDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckDumpUserDataByUserId(
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
            
        }
        const auto Domain = Self;
        Domain->Url = Domain->Url = ResultModel->GetUrl();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2LotteryDomain::FCheckDumpUserDataTask>> FGs2LotteryDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2LotteryDomain::FCleanUserDataTask::FCleanUserDataTask(
        TSharedPtr<FGs2LotteryDomain> Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2LotteryDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2LotteryDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2LotteryDomain>> Result
    )
    {
        const auto Future = Self->Client->CleanUserDataByUserId(
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
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2LotteryDomain::FCleanUserDataTask>> FGs2LotteryDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2LotteryDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        TSharedPtr<FGs2LotteryDomain> Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2LotteryDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2LotteryDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2LotteryDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckCleanUserDataByUserId(
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
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2LotteryDomain::FCheckCleanUserDataTask>> FGs2LotteryDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Lottery::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2LotteryDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Lottery::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2LotteryDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Lottery::Model::FNamespace::TypeName,
            "lottery:Namespace",
            Callback
        );
    }

    void FGs2LotteryDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Lottery::Model::FNamespace::TypeName,
            "lottery:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Lottery::Domain::Model::FNamespaceDomain> FGs2LotteryDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Lottery::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }
    FDrawnResultEvent& FGs2LotteryDomain::OnDrawnResult()
    {
        return DrawnResultEvent;
    }

    void FGs2LotteryDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "DrawByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Lottery::Request::FDrawByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Lottery::Result::FDrawByUserIdResult::FromJson(ResultModelJson);
            
            DrawnResultEvent.Broadcast(
                RequestModel->GetNamespaceName(),
                RequestModel->GetLotteryName(),
                ResultModel->GetItems()
            );
        }
    }

    void FGs2LotteryDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2LotteryDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "draw_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Lottery::Request::FDrawByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Lottery::Result::FDrawByUserIdResult::FromJson(ResultModelJson);
            
            DrawnResultEvent.Broadcast(
                RequestModel->GetNamespaceName(),
                RequestModel->GetLotteryName(),
                ResultModel->GetItems()
            );
        }
    }

    void FGs2LotteryDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

