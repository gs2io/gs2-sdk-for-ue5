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

#include "LoginReward/Domain/Gs2LoginReward.h"
#include "LoginReward/Domain/Model/Namespace.h"
#include "LoginReward/Domain/Model/BonusModelMaster.h"
#include "LoginReward/Domain/Model/CurrentBonusMaster.h"
#include "LoginReward/Domain/Model/BonusModel.h"
#include "LoginReward/Domain/Model/User.h"
#include "LoginReward/Domain/Model/UserAccessToken.h"
#include "LoginReward/Domain/Model/Bonus.h"
#include "LoginReward/Domain/Model/ReceiveStatus.h"

namespace Gs2::LoginReward::Domain
{

    FGs2LoginRewardDomain::FGs2LoginRewardDomain(
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
        Client(MakeShared<Gs2::LoginReward::FGs2LoginRewardRestClient>(Session)),
        ParentKey("loginReward")
    {
    }

    FGs2LoginRewardDomain::FGs2LoginRewardDomain(
        const FGs2LoginRewardDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2LoginRewardDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2LoginRewardDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2LoginRewardDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2LoginRewardDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("loginReward:Namespace");
                const auto Key = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::LoginReward::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::LoginReward::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2LoginRewardDomain::FCreateNamespaceTask>> FGs2LoginRewardDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::LoginReward::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2LoginRewardDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    TSharedPtr<Gs2::LoginReward::Domain::Model::FNamespaceDomain> FGs2LoginRewardDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::LoginReward::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2LoginRewardDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "DeleteReceiveStatusByUserId") {
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
            const auto RequestModel = Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::LoginReward::Result::FDeleteReceiveStatusByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "ReceiveStatus"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetBonusModelName()
                );
                Cache->Delete(Gs2::LoginReward::Model::FReceiveStatus::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetBonusModel() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "BonusModel"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FBonusModelDomain::CreateCacheKey(
                    ResultModel->GetBonusModel()->GetName()
                );
                Cache->Delete(Gs2::LoginReward::Model::FBonusModel::TypeName, ParentKey, Key);
            }
        }
        if (Method == "UnmarkReceivedByUserId") {
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
            const auto RequestModel = Gs2::LoginReward::Request::FUnmarkReceivedByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::LoginReward::Result::FUnmarkReceivedByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "ReceiveStatus"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetBonusModelName()
                );
                Cache->Put(
                    Gs2::LoginReward::Model::FReceiveStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetBonusModel() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "BonusModel"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FBonusModelDomain::CreateCacheKey(
                    ResultModel->GetBonusModel()->GetName()
                );
                Cache->Put(
                    Gs2::LoginReward::Model::FBonusModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetBonusModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2LoginRewardDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "MarkReceivedByUserId") {
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
            const auto RequestModel = Gs2::LoginReward::Request::FMarkReceivedByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::LoginReward::Result::FMarkReceivedByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "ReceiveStatus"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetBonusModelName()
                );
                Cache->Put(
                    Gs2::LoginReward::Model::FReceiveStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetBonusModel() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "BonusModel"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FBonusModelDomain::CreateCacheKey(
                    ResultModel->GetBonusModel()->GetName()
                );
                Cache->Put(
                    Gs2::LoginReward::Model::FBonusModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetBonusModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2LoginRewardDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "delete_receive_status_by_user_id") {
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
            const auto RequestModel = Gs2::LoginReward::Request::FDeleteReceiveStatusByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::LoginReward::Result::FDeleteReceiveStatusByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "ReceiveStatus"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetBonusModelName()
                );
                Cache->Delete(Gs2::LoginReward::Model::FReceiveStatus::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetBonusModel() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "BonusModel"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FBonusModelDomain::CreateCacheKey(
                    ResultModel->GetBonusModel()->GetName()
                );
                Cache->Delete(Gs2::LoginReward::Model::FBonusModel::TypeName, ParentKey, Key);
            }
        }
        if (Method == "unmark_received_by_user_id") {
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
            const auto RequestModel = Gs2::LoginReward::Request::FUnmarkReceivedByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::LoginReward::Result::FUnmarkReceivedByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "ReceiveStatus"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetBonusModelName()
                );
                Cache->Put(
                    Gs2::LoginReward::Model::FReceiveStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetBonusModel() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "BonusModel"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FBonusModelDomain::CreateCacheKey(
                    ResultModel->GetBonusModel()->GetName()
                );
                Cache->Put(
                    Gs2::LoginReward::Model::FBonusModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetBonusModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2LoginRewardDomain::HandleNotification(
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

