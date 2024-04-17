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

#include "Core/Domain/Gs2.h"

#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Task/RestCloseTask.h"
#include "Core/Net/WebSocket/Task/WebSocketCloseTask.h"
#include "JobQueue/Domain/Model/JobAccessToken.h"
#include "JobQueue/Domain/Model/UserAccessToken.h"


namespace Gs2::Core::Domain
{
    FGs2::FGs2(
        Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession,
        Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr _WebSocketSession,
        TOptional<FString> DistributorNamespaceName
    ):
        Cache(MakeShared<Core::Domain::FCacheDatabase>()),
        JobQueueDomain(MakeShared<Core::Domain::Model::FJobQueueDomain>(
            [&](
                const Gs2::JobQueue::Model::FJobPtr& Job,
                const Gs2::JobQueue::Model::FJobResultBodyPtr& Result
            )
            {
                UE_LOG(Gs2Log, Verbose, TEXT("JobQueueResult [%s] %s"), ToCStr(*Job->GetName()), ToCStr(*Result->GetResult()));
                UpdateCacheFromJobResult(Job, Result);
            }
        )),
        TransactionConfiguration(MakeShared<Core::Domain::Model::FTransactionConfiguration>(
            DistributorNamespaceName,
            [&](const FString Action, const FString Request, const FString Result)
            {
                UE_LOG(Gs2Log, Verbose, TEXT("StampTaskResult [%s][%s] %s"), ToCStr(Action), ToCStr(Request), ToCStr(Result));
                UpdateCacheFromStampTask(Action, Request, Result);
            },
            [&](const FString Action, const FString Request, const FString Result)
            {
                UE_LOG(Gs2Log, Verbose, TEXT("StampSheetResult [%s][%s] %s"), ToCStr(Action), ToCStr(Request), ToCStr(Result));
                UpdateCacheFromStampSheet(Action, Request, Result);
            }
        )),
        RestSession(RestSession),
        WebSocketSession(_WebSocketSession),
        DistributorNamespaceName(DistributorNamespaceName),
        Account(nullptr),
        AdReward(nullptr),
        Auth(nullptr),
        Buff(nullptr),
        Chat(nullptr),
        Datastore(nullptr),
        Deploy(nullptr),
        Dictionary(nullptr),
        Distributor(nullptr),
        Enchant(nullptr),
        Enhance(nullptr),
        Exchange(nullptr),
        Experience(nullptr),
        Formation(nullptr),
        Friend(nullptr),
        Gateway(nullptr),
        Grade(nullptr),
        Identifier(nullptr),
        Idle(nullptr),
        Inbox(nullptr),
        Inventory(nullptr),
        JobQueue(nullptr),
        Key(nullptr),
        Limit(nullptr),
        LoginReward(nullptr),
        Lock(nullptr),
        Lottery(nullptr),
        Matchmaking(nullptr),
        MegaField(nullptr),
        Mission(nullptr),
        Money(nullptr),
        News(nullptr),
        Quest(nullptr),
        Ranking(nullptr),
        Realtime(nullptr),
        Schedule(nullptr),
        Script(nullptr),
        SeasonRating(nullptr),
        SerialKey(nullptr),
        Showcase(nullptr),
        SkillTree(nullptr),
        Stamina(nullptr),
        StateMachine(nullptr),
        Version(nullptr),
        Disposed(false)
    {
        if (WebSocketSession.IsValid())
        {
            WebSocketSession->OnNotification().AddLambda([&](Core::Domain::Model::FNotificationMessagePtr Message)
            {
                if (Disposed)
                {
                    UE_LOG(Gs2Log, Error, TEXT("[WebSocketSession::OnNotification] FGs2 already disposed"));
                    return;
                }
                if (WebSocketSession->Disposed)
                {
                    UE_LOG(Gs2Log, Error, TEXT("[WebSocketSession::OnNotification] FGs2WebSocketSession already disposed"));
                    return;
                }
                if (Message->GetSubject()->Contains(":") && Message->GetPayload().IsSet())
                {
                    auto Service = FString("");
                    auto Method = FString("");
                    Message->GetSubject()->Split(FString(":"), &Service, &Method);
                    if (Service == "Gs2Account")
                    {
                        Account->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2AdReward")
                    {
                        AdReward->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Auth")
                    {
                        Auth->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Buff")
                    {
                        Buff->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Chat")
                    {
                        Chat->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Datastore")
                    {
                        Datastore->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Dictionary")
                    {
                        Dictionary->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Distributor")
                    {
                        Distributor->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Enchant")
                    {
                        Enchant->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Enhance")
                    {
                        Enhance->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Exchange")
                    {
                        Exchange->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Experience")
                    {
                        Experience->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Formation")
                    {
                        Formation->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Friend")
                    {
                        Friend->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Gateway")
                    {
                        Gateway->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Grade")
                    {
                        Grade->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Identifier")
                    {
                        Identifier->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Idle")
                    {
                        Idle->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Inbox")
                    {
                        Inbox->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Inventory")
                    {
                        Inventory->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2JobQueue")
                    {
                        JobQueue->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Key")
                    {
                        Key->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Limit")
                    {
                        Limit->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2LoginReward")
                    {
                        LoginReward->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Lock")
                    {
                        Lock->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Lottery")
                    {
                        Lottery->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Matchmaking")
                    {
                        Matchmaking->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2MegaField")
                    {
                        MegaField->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Mission")
                    {
                        Mission->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Money")
                    {
                        Money->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2News")
                    {
                        News->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Quest")
                    {
                        Quest->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Ranking")
                    {
                        Ranking->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Realtime")
                    {
                        Realtime->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Schedule")
                    {
                        Schedule->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Script")
                    {
                        Script->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2SeasonRating")
                    {
                        SeasonRating->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2SerialKey")
                    {
                        SerialKey->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Showcase")
                    {
                        Showcase->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2SkillTree")
                    {
                        SkillTree->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Stamina")
                    {
                        Stamina->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2StateMachine")
                    {
                        StateMachine->HandleNotification(Method, *Message->GetPayload());
                    }
                    if (Service == "Gs2Version")
                    {
                        Version->HandleNotification(Method, *Message->GetPayload());
                    }
                }
            });
        }
    }

    FGs2::FGs2(
        const FGs2& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        TransactionConfiguration(From.TransactionConfiguration),
        RestSession(From.RestSession),
        WebSocketSession(From.WebSocketSession),
        DistributorNamespaceName(From.DistributorNamespaceName),
        Account(From.Account),
        AdReward(From.AdReward),
        Auth(From.Auth),
        Buff(From.Buff),
        Chat(From.Chat),
        Datastore(From.Datastore),
        Dictionary(From.Dictionary),
        Distributor(From.Distributor),
        Enchant(From.Enchant),
        Enhance(From.Enhance),
        Exchange(From.Exchange),
        Experience(From.Experience),
        Formation(From.Formation),
        Friend(From.Friend),
        Gateway(From.Gateway),
        Grade(From.Grade),
        Identifier(From.Identifier),
        Idle(From.Idle),
        Inbox(From.Inbox),
        Inventory(From.Inventory),
        JobQueue(From.JobQueue),
        Key(From.Key),
        Limit(From.Limit),
        LoginReward(From.LoginReward),
        Lock(From.Lock),
        Lottery(From.Lottery),
        Matchmaking(From.Matchmaking),
        MegaField(From.MegaField),
        Mission(From.Mission),
        Money(From.Money),
        News(From.News),
        Quest(From.Quest),
        Ranking(From.Ranking),
        Realtime(From.Realtime),
        Schedule(From.Schedule),
        Script(From.Script),
        SeasonRating(From.SeasonRating),
        SerialKey(From.SerialKey),
        Showcase(From.Showcase),
        SkillTree(From.SkillTree),
        Stamina(From.Stamina),
        StateMachine(From.StateMachine),
        Version(From.Version),
        Disposed(From.Disposed)
    {
    }

    FGs2::~FGs2()
    {
        Disposed = true;
    }

    void FGs2::Initialize()
    {
        Account = MakeShared<Account::Domain::FGs2AccountDomain>(SharedThis(this));
        AdReward = MakeShared<AdReward::Domain::FGs2AdRewardDomain>(SharedThis(this));
        Auth = MakeShared<Auth::Domain::FGs2AuthDomain>(SharedThis(this));
        Buff = MakeShared<Buff::Domain::FGs2BuffDomain>(SharedThis(this));
        Chat = MakeShared<Chat::Domain::FGs2ChatDomain>(SharedThis(this));
        Datastore = MakeShared<Datastore::Domain::FGs2DatastoreDomain>(SharedThis(this));
        Deploy = MakeShared<Deploy::Domain::FGs2DeployDomain>(SharedThis(this));
        Dictionary = MakeShared<Dictionary::Domain::FGs2DictionaryDomain>(SharedThis(this));
        Distributor = MakeShared<Distributor::Domain::FGs2DistributorDomain>(SharedThis(this));
        Enchant = MakeShared<Enchant::Domain::FGs2EnchantDomain>(SharedThis(this));
        Enhance = MakeShared<Enhance::Domain::FGs2EnhanceDomain>(SharedThis(this));
        Exchange = MakeShared<Exchange::Domain::FGs2ExchangeDomain>(SharedThis(this));
        Experience = MakeShared<Experience::Domain::FGs2ExperienceDomain>(SharedThis(this));
        Formation = MakeShared<Formation::Domain::FGs2FormationDomain>(SharedThis(this));
        Friend = MakeShared<Friend::Domain::FGs2FriendDomain>(SharedThis(this));
        Gateway = MakeShared<Gateway::Domain::FGs2GatewayDomain>(SharedThis(this));
        Grade = MakeShared<Grade::Domain::FGs2GradeDomain>(SharedThis(this));
        Identifier = MakeShared<Identifier::Domain::FGs2IdentifierDomain>(SharedThis(this));
        Idle = MakeShared<Idle::Domain::FGs2IdleDomain>(SharedThis(this));
        Inbox = MakeShared<Inbox::Domain::FGs2InboxDomain>(SharedThis(this));
        Inventory = MakeShared<Inventory::Domain::FGs2InventoryDomain>(SharedThis(this));
        JobQueue = MakeShared<JobQueue::Domain::FGs2JobQueueDomain>(SharedThis(this));
        Key = MakeShared<Key::Domain::FGs2KeyDomain>(SharedThis(this));
        Limit = MakeShared<Limit::Domain::FGs2LimitDomain>(SharedThis(this));
        LoginReward = MakeShared<LoginReward::Domain::FGs2LoginRewardDomain>(SharedThis(this));
        Lock = MakeShared<Lock::Domain::FGs2LockDomain>(SharedThis(this));
        Lottery = MakeShared<Lottery::Domain::FGs2LotteryDomain>(SharedThis(this));
        Matchmaking = MakeShared<Matchmaking::Domain::FGs2MatchmakingDomain>(SharedThis(this));
        MegaField = MakeShared<MegaField::Domain::FGs2MegaFieldDomain>(SharedThis(this));
        Mission = MakeShared<Mission::Domain::FGs2MissionDomain>(SharedThis(this));
        Money = MakeShared<Money::Domain::FGs2MoneyDomain>(SharedThis(this));
        News = MakeShared<News::Domain::FGs2NewsDomain>(SharedThis(this));
        Quest = MakeShared<Quest::Domain::FGs2QuestDomain>(SharedThis(this));
        Ranking = MakeShared<Ranking::Domain::FGs2RankingDomain>(SharedThis(this));
        Realtime = MakeShared<Realtime::Domain::FGs2RealtimeDomain>(SharedThis(this));
        Schedule = MakeShared<Schedule::Domain::FGs2ScheduleDomain>(SharedThis(this));
        Script = MakeShared<Script::Domain::FGs2ScriptDomain>(SharedThis(this));
        SeasonRating = MakeShared<SeasonRating::Domain::FGs2SeasonRatingDomain>(SharedThis(this));
        SerialKey = MakeShared<SerialKey::Domain::FGs2SerialKeyDomain>(SharedThis(this));
        Showcase = MakeShared<Showcase::Domain::FGs2ShowcaseDomain>(SharedThis(this));
        SkillTree = MakeShared<SkillTree::Domain::FGs2SkillTreeDomain>(SharedThis(this));
        Stamina = MakeShared<Stamina::Domain::FGs2StaminaDomain>(SharedThis(this));
        StateMachine = MakeShared<StateMachine::Domain::FGs2StateMachineDomain>(SharedThis(this));
        Version = MakeShared<Version::Domain::FGs2VersionDomain>(SharedThis(this));
        
        const auto IssueTransactionAction = [this](Gs2::Core::Domain::Model::FIssueTransactionEventPtr e)
        {
            TransactionExecute(
                e->GetAccessToken(),
                e->GetConsumeActions(),
                e->GetAcquireActions(),
                e->GetRate()
            );
        };
        Account->OnIssueTransaction.AddLambda(IssueTransactionAction);
        AdReward->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Buff->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Chat->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Datastore->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Deploy->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Dictionary->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Distributor->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Enchant->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Enhance->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Exchange->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Experience->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Formation->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Friend->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Gateway->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Grade->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Identifier->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Idle->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Inbox->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Inventory->OnIssueTransaction.AddLambda(IssueTransactionAction);
        JobQueue->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Key->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Limit->OnIssueTransaction.AddLambda(IssueTransactionAction);
        LoginReward->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Lock->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Lottery->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Matchmaking->OnIssueTransaction.AddLambda(IssueTransactionAction);
        MegaField->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Mission->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Money->OnIssueTransaction.AddLambda(IssueTransactionAction);
        News->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Quest->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Ranking->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Realtime->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Schedule->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Script->OnIssueTransaction.AddLambda(IssueTransactionAction);
        SeasonRating->OnIssueTransaction.AddLambda(IssueTransactionAction);
        SerialKey->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Showcase->OnIssueTransaction.AddLambda(IssueTransactionAction);
        SkillTree->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Stamina->OnIssueTransaction.AddLambda(IssueTransactionAction);
        StateMachine->OnIssueTransaction.AddLambda(IssueTransactionAction);
        Version->OnIssueTransaction.AddLambda(IssueTransactionAction);
        
    }

    void FGs2::UpdateCacheFromStampSheet(const FString Action, const FString Request, const FString Result) const
    {
        if (Disposed)
        {
            UE_LOG(Gs2Log, Error, TEXT("[WebSocketSession::OnNotification] FGs2 already disposed"));
            return;
        }
        if (Result.StartsWith("{\"message\":\""))
        {
            UE_LOG(Gs2Log, Error, TEXT("%s"), ToCStr(Result));
            return;
        }
        if (Action.Contains(":"))
        {
            auto Service = FString("");
            auto Method = FString("");
            Action.Split(FString(":"), &Service, &Method);
            
            if (Service == "Gs2Account")
            {
                Account->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2AdReward")
            {
                AdReward->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Auth")
            {
                Auth->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Buff")
            {
                Buff->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Chat")
            {
                Chat->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Datastore")
            {
                Datastore->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Dictionary")
            {
                Dictionary->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Distributor")
            {
                Distributor->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Enchant")
            {
                Enchant->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Enhance")
            {
                Enhance->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Exchange")
            {
                Exchange->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Experience")
            {
                Experience->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Formation")
            {
                Formation->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Friend")
            {
                Friend->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Gateway")
            {
                Gateway->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Grade")
            {
                Grade->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Identifier")
            {
                Identifier->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Idle")
            {
                Idle->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Inbox")
            {
                Inbox->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Inventory")
            {
                Inventory->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2JobQueue")
            {
                JobQueue->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Key")
            {
                Key->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Limit")
            {
                Limit->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2LoginReward")
            {
                LoginReward->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Lock")
            {
                Lock->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Lottery")
            {
                Lottery->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Matchmaking")
            {
                Matchmaking->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2MegaField")
            {
                MegaField->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Mission")
            {
                Mission->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Money")
            {
                Money->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2News")
            {
                News->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Quest")
            {
                Quest->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Ranking")
            {
                Ranking->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Realtime")
            {
                Realtime->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Schedule")
            {
                Schedule->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Script")
            {
                Script->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2SeasonRating")
            {
                SeasonRating->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2SerialKey")
            {
                SerialKey->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Showcase")
            {
                Showcase->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2SkillTree")
            {
                SkillTree->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Stamina")
            {
                Stamina->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2StateMachine")
            {
                StateMachine->UpdateCacheFromStampSheet(Method, Request, Result);
            }
            if (Service == "Gs2Version")
            {
                Version->UpdateCacheFromStampSheet(Method, Request, Result);
            }
        }
    }

    void FGs2::UpdateCacheFromStampTask(const FString Action, const FString Request, const FString Result) const
    {
        if (Disposed)
        {
            UE_LOG(Gs2Log, Error, TEXT("[WebSocketSession::OnNotification] FGs2 already disposed"));
            return;
        }
        if (Result.StartsWith("{\"message\":\""))
        {
            UE_LOG(Gs2Log, Error, TEXT("%s"), ToCStr(Result));
            return;
        }
        if (Action.Contains(":"))
        {
            auto Service = FString("");
            auto Method = FString("");
            Action.Split(FString(":"), &Service, &Method);
            
            if (Service == "Gs2Account")
            {
                Account->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2AdReward")
            {
                AdReward->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Auth")
            {
                Auth->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Buff")
            {
                Buff->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Chat")
            {
                Chat->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Datastore")
            {
                Datastore->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Dictionary")
            {
                Dictionary->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Distributor")
            {
                Distributor->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Enchant")
            {
                Enchant->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Enhance")
            {
                Enhance->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Exchange")
            {
                Exchange->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Experience")
            {
                Experience->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Formation")
            {
                Formation->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Friend")
            {
                Friend->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Gateway")
            {
                Gateway->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Grade")
            {
                Grade->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Identifier")
            {
                Identifier->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Idle")
            {
                Idle->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Inbox")
            {
                Inbox->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Inventory")
            {
                Inventory->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2JobQueue")
            {
                JobQueue->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Key")
            {
                Key->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Limit")
            {
                Limit->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2LoginReward")
            {
                LoginReward->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Lock")
            {
                Lock->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Lottery")
            {
                Lottery->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Matchmaking")
            {
                Matchmaking->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2MegaField")
            {
                MegaField->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Mission")
            {
                Mission->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Money")
            {
                Money->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2News")
            {
                News->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Quest")
            {
                Quest->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Ranking")
            {
                Ranking->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Realtime")
            {
                Realtime->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Schedule")
            {
                Schedule->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Script")
            {
                Script->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2SeasonRating")
            {
                SeasonRating->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2SerialKey")
            {
                SerialKey->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Showcase")
            {
                Showcase->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2SkillTree")
            {
                SkillTree->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Stamina")
            {
                Stamina->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2StateMachine")
            {
                StateMachine->UpdateCacheFromStampTask(Method, Request, Result);
            }
            if (Service == "Gs2Version")
            {
                Version->UpdateCacheFromStampTask(Method, Request, Result);
            }
        }
    }

    void FGs2::PushJobQueue(TOptional<FString> NamespaceName) const
    {
        if (NamespaceName.IsSet())
        {
            JobQueueDomain->Push(*NamespaceName);
        }
    }

    void FGs2::UpdateCacheFromJobResult(Gs2::JobQueue::Model::FJobPtr Job, Gs2::JobQueue::Model::FJobResultBodyPtr Result)
    {
        if (Disposed)
        {
            UE_LOG(Gs2Log, Error, TEXT("[WebSocketSession::OnNotification] FGs2 already disposed"));
            return;
        }
        if (!Job->GetScriptId().IsSet())
        {
            return;
        }
        const auto OwnerId = Script::Model::FScript::GetOwnerIdFromGrn(*Job->GetScriptId());
        if (!OwnerId.IsSet())
        {
            return;
        }
        if (*OwnerId == "system")
        {
            auto ScriptName = Script::Model::FScript::GetScriptNameFromGrn(*Job->GetScriptId());
            if (!ScriptName.IsSet())
            {
                return;
            }
            ScriptName = ScriptName->Replace(TEXT("execute_"), TEXT(""));
            
            auto Service = FString("");
            auto Method = FString("");
            ScriptName->Split(FString("_"), &Service, &Method);
            
            if (Service == "account")
            {
                Account->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "ad_reward")
            {
                AdReward->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "auth")
            {
                Auth->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "buff")
            {
                Buff->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "chat")
            {
                Chat->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "datastore")
            {
                Datastore->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "dictionary")
            {
                Dictionary->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "distributor")
            {
                Distributor->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "enchant")
            {
                Enchant->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "enhance")
            {
                Enhance->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "exchange")
            {
                Exchange->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "experience")
            {
                Experience->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "formation")
            {
                Formation->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "friend")
            {
                Friend->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "gateway")
            {
                Gateway->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "grade")
            {
                Grade->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "identifier")
            {
                Identifier->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "idle")
            {
                Idle->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "inbox")
            {
                Inbox->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "inventory")
            {
                Inventory->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "job_queue")
            {
                JobQueue->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "key")
            {
                Key->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "limit")
            {
                Limit->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "login_reward")
            {
                LoginReward->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "lock")
            {
                Lock->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "lottery")
            {
                Lottery->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "matchmaking")
            {
                Matchmaking->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "megaField")
            {
                MegaField->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "mission")
            {
                Mission->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "money")
            {
                Money->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "news")
            {
                News->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "quest")
            {
                Quest->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "ranking")
            {
                Ranking->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "realtime")
            {
                Realtime->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "schedule")
            {
                Schedule->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "script")
            {
                Script->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "season_rating")
            {
                SeasonRating->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "serial_key")
            {
                SerialKey->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "showcase")
            {
                Showcase->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "skill_tree")
            {
                SkillTree->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "stamina")
            {
                Stamina->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "state_machine")
            {
                StateMachine->UpdateCacheFromJobResult(Method, Job, Result);
            }
            if (Service == "version")
            {
                Version->UpdateCacheFromJobResult(Method, Job, Result);
            }
        }
    }

    FGs2::FDispatchTask::FDispatchTask(
        const TSharedPtr<FGs2> Self,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
    ): Self(Self), AccessToken(AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2::FDispatchTask::Action(
        TSharedPtr<TSharedPtr<void*>> Result
    )
    {
        {
            const auto Future = Self->Distributor->Dispatch(AccessToken);
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            Future->EnsureCompletion();
        }
        {
            const auto Future = Self->JobQueue->Dispatch(AccessToken);
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            Future->EnsureCompletion();
        }
        
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2::FDispatchTask>> FGs2::Dispatch(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDispatchTask>>(SharedThis(this), AccessToken);
    }

    FGs2::FDispatchByUserIdTask::FDispatchByUserIdTask(
        const TSharedPtr<FGs2> Self,
        const FString UserId
    ):
        Self(Self),
        UserId(UserId)
    {
        
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2::FDispatchByUserIdTask::Action(
        TSharedPtr<TSharedPtr<void*>> Result
    )
    {
        {
            const auto Future = Self->Distributor->DispatchByUserId(UserId);
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            Future->EnsureCompletion();
        }
        {
            const auto Future = Self->JobQueue->DispatchByUserId(UserId);
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            Future->EnsureCompletion();
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2::FDispatchByUserIdTask>> FGs2::DispatchByUserId(
        const FString UserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDispatchByUserIdTask>>(SharedThis(this), UserId);
    }

    FGs2::FDisconnectTask::FDisconnectTask(const TSharedPtr<FGs2> Self): Self(Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2::FDisconnectTask::Action(
        TSharedPtr<TSharedPtr<void*>> Result
    )
    {
        const auto RestCloseFuture = Self->RestSession->Close();
        RestCloseFuture->StartSynchronousTask();
        if (RestCloseFuture->GetTask().IsError())
        {
            return RestCloseFuture->GetTask().Error();
        }
        RestCloseFuture->EnsureCompletion();
        
        const auto WebSocketCloseFuture = Self->WebSocketSession->Close();
        WebSocketCloseFuture->StartSynchronousTask();
        if (WebSocketCloseFuture->GetTask().IsError())
        {
            return WebSocketCloseFuture->GetTask().Error();
        }
        WebSocketCloseFuture->EnsureCompletion();
        
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2::FDisconnectTask>> FGs2::Disconnect()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDisconnectTask>>(SharedThis(this));
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2::TransactionExecute(const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>& ConsumeActions,
        const TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>>& AcquireAction,
        TBigInt<1024, false> Rate
    )
    {
        const auto Future = MakeShared<SpeculativeExecutor::FSpeculativeExecutor>(
            ConsumeActions,
            AcquireAction,
            Rate
        )->Execute(
            AsShared(),
            AccessToken
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        return nullptr;
    }
}
