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

#include "Inbox/Domain/SpeculativeExecutor/Consume/DeleteMessageByUserIdSpeculativeExecutor.h"
#include "Inbox/Domain/Gs2Inbox.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "Inbox/Model/Cache/Namespace.h"
#include "Inbox/Model/Cache/Message.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Inbox::Domain::SpeculativeExecutor
{

    namespace
    {
        FString DeleteMessageSnapshot(const Gs2::Inbox::Model::FNamespacePtr& Item)
        {
            FString Value;
            auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Value);
            FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer);
            return Value;
        }

        FString DeleteMessageSnapshot(const Gs2::Inbox::Model::FMessagePtr& Item)
        {
            FString Value;
            auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Value);
            FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer);
            return Value;
        }
    }

    FString FDeleteMessageByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inbox:DeleteMessageByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteMessageByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inbox::Request::FDeleteMessageByUserIdRequestPtr& Request,
        Gs2::Inbox::Model::FMessagePtr Item
    )
    {
        return nullptr;
    }

    FDeleteMessageByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inbox::Domain::FGs2InboxDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inbox::Request::FDeleteMessageByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteMessageByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteMessageByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !AccessToken.IsValid() || !Request.IsValid()) return nullptr;
        const auto Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto Prepared = MakeShared<Gs2::Inbox::Request::FDeleteMessageByUserIdRequest>(*Request);
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() || !Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() || !Prepared->GetMessageName().IsSet() || Prepared->GetMessageName().Get(FString()).IsEmpty()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const auto MessageName = Prepared->GetMessageName();
        const auto UserId = Token->GetUserId();
        const auto TimeOffset = Token->GetTimeOffset();
        const auto Region = Domain->RestSession->RegionName();
        const auto OwnerId = Domain->RestSession->OwnerId();
        Gs2::Inbox::Model::FNamespacePtr NamespaceModel;
        if (!Gs2::Inbox::Model::Cache::FNamespaceCache::TryGet(Domain->Cache, NamespaceName, TOptional<int32>(), &NamespaceModel) || !NamespaceModel.IsValid() || !NamespaceModel->GetName().IsSet() || NamespaceModel->GetName().Get(FString()) != NamespaceName.Get(FString()) || !NamespaceModel->GetIsAutomaticDeletingEnabled().IsSet() || !NamespaceModel->GetCreatedAt().IsSet() || NamespaceModel->GetNamespaceId().Get(FString()) != FString::Printf(TEXT("grn:gs2:%s:%s:inbox:%s"), *Region, *OwnerId, *NamespaceName.Get(FString()))) return nullptr;
        Gs2::Inbox::Model::FMessagePtr Item;
        const bool Found = Gs2::Inbox::Model::Cache::FMessageCache::TryGet(Domain->Cache, NamespaceName, UserId, MessageName, TimeOffset, &Item);
        const int64 PhysicalTimeMillis = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0);
        const auto ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:inbox:%s:user:%s:message:%s"), *Region, *OwnerId, *NamespaceName.Get(FString()), *UserId.Get(FString()), *MessageName.Get(FString()));
        if (!Found || !Item.IsValid() || Item->GetMessageId().Get(FString()) != ExpectedId || Item->GetName().Get(FString()) != MessageName.Get(FString()) || Item->GetUserId().Get(FString()) != UserId.Get(FString()) || !Item->GetReceivedAt().IsSet() || Item->GetReceivedAt().Get(0) < NamespaceModel->GetCreatedAt().Get(0) || (Item->GetExpiresAt().IsSet() && Item->GetExpiresAt().Get(0) < PhysicalTimeMillis)) return nullptr;
        const auto ExpectedNamespace = MakeShared<Gs2::Inbox::Model::FNamespace>(*NamespaceModel);
        const auto Expected = MakeShared<Gs2::Inbox::Model::FMessage>(*Item);
        const auto NamespaceSnapshot = DeleteMessageSnapshot(ExpectedNamespace);
        const auto MessageSnapshot = DeleteMessageSnapshot(Expected);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>(
            [DomainCopy = Domain, NamespaceName, UserId, MessageName, TimeOffset, NamespaceSnapshot, MessageSnapshot]()
        {
            Gs2::Inbox::Model::FNamespacePtr LiveNamespace;
            Gs2::Inbox::Model::FMessagePtr LiveMessage;
            if (!Gs2::Inbox::Model::Cache::FNamespaceCache::TryGet(DomainCopy->Cache, NamespaceName, TOptional<int32>(), &LiveNamespace) || !LiveNamespace.IsValid() || DeleteMessageSnapshot(LiveNamespace) != NamespaceSnapshot || !Gs2::Inbox::Model::Cache::FMessageCache::TryGet(DomainCopy->Cache, NamespaceName, UserId, MessageName, TimeOffset, &LiveMessage) || !LiveMessage.IsValid() || DeleteMessageSnapshot(LiveMessage) != MessageSnapshot) return;
            Gs2::Inbox::Model::Cache::FMessageCache::Put(DomainCopy->Cache, NamespaceName, UserId, MessageName, TimeOffset, nullptr);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteMessageByUserIdSpeculativeExecutor::FCommitTask>> FDeleteMessageByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inbox::Domain::FGs2InboxDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inbox::Request::FDeleteMessageByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inbox::Request::FDeleteMessageByUserIdRequestPtr FDeleteMessageByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inbox::Request::FDeleteMessageByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Inbox::Request::FDeleteMessageByUserIdRequestPtr FDeleteMessageByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inbox::Request::FDeleteMessageByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
